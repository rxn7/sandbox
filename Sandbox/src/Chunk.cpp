#include "core/Math.h"
#include "World.h"
#include "Definitions.h"
#include "BlocksContainer.h"
#include "core/render/Shader.h"
#include <iostream>
#include "Structures.h"

Chunk::Chunk(World& world, ChunkCoord coord) 
: mp_world(&world), m_coord(coord), m_update(false), m_createMesh(false){
	GenerateTerrain();
	m_update = true;
}

Chunk::~Chunk() {
	delete mp_mesh;
}

void Chunk::GenerateTerrain() {
	for (int x = 0; x<CHUNK_WIDTH; x++) {
		for (int z = 0; z<CHUNK_WIDTH; z++) {
			uint8_t height = mp_world->GetHeight(x + m_coord.x * CHUNK_WIDTH, z + m_coord.y * CHUNK_WIDTH);
			m_map[x][height][z].SetType(TYPE_GRASS);
			
			int y = height;
			y--;
			for (; y>0; y--) {
				m_map[x][y][z].SetType(TYPE_DIRT);
			}
			
			m_map[x][0][z].SetType(TYPE_BEDROCK);
		}
	}
}

void Chunk::Update() {
	m_update = false;

	ClearMeshData();
	
	for (int x = 0; x<CHUNK_WIDTH; x++) {
		for (int y = 0; y<CHUNK_HEIGHT; y++) {
			for (int z = 0; z<CHUNK_WIDTH; z++) {
				UpdateMeshData(glm::i16vec3(x, y, z));
			}
		}
	}

	m_createMesh = true;
}

void Chunk::Draw(Shader& shader, const Camera& camera) {
	if (mp_mesh) {
		mp_mesh->Draw(camera, shader, m_coord);
	}
}

void Chunk::ClearMeshData() {
	m_vertexIndex = 0;
	m_vertices.clear();
	m_triangles.clear();
	m_texCoords.clear();
}

bool Chunk::ShouldRenderFace(const glm::i8vec3& pos) {
	if (pos.y < 0) {
		return false;
	} else if (pos.y>=CHUNK_HEIGHT) {
		return true;
	}

	if (pos.x < 0 || pos.x >= CHUNK_WIDTH || pos.z < 0 || pos.z >= CHUNK_WIDTH) {
		return Blocks::BLOCK_TYPES[mp_world->GetBlock(GetGlobalPos(pos))]->ShouldRenderNeighbours();
	}

	return m_map[pos.x][pos.y][pos.z].GetType()->ShouldRenderNeighbours();
}

void Chunk::UpdateMeshData(const glm::i16vec3& pos) {
	if (GetBlockID(pos) == TYPE_AIR) return;
	
	for (uint8_t f = 0; f<6; f++) { /* Each block has 6 faces */
		if (ShouldRenderFace(pos + FACES[f])) {
			Block& block = m_map[pos.x][pos.y][pos.z];

			for (int i = 0; i<4; i++) {	/* Each face has 4 vertices */
				m_vertices.push_back(pos + VERTICES[TRIANGLES[f][i]]);
			}
			
			AddTexture(block.GetTextureID(f));

			m_triangles.push_back(m_vertexIndex);
			m_triangles.push_back(m_vertexIndex+1);
			m_triangles.push_back(m_vertexIndex+2);
			m_triangles.push_back(m_vertexIndex+2);
			m_triangles.push_back(m_vertexIndex+1);
			m_triangles.push_back(m_vertexIndex+3);

			m_vertexIndex += 4;
		}
	}
}

void Chunk::CreateMesh() {
	m_createMesh = false;
	delete mp_mesh;

	std::vector<Vertex> vertices;
	
	for (size_t i = 0; i<m_vertices.size(); i++) {
		vertices.push_back(Vertex(m_vertices[i], m_texCoords[i]));
	}

	mp_mesh = new Mesh(vertices, m_triangles);
}

void Chunk::AddTexture(uint16_t texID) {
	double y = texID / ATLAS_SIZE;
	double x = texID - (y * ATLAS_SIZE);
	
	x *= TEX_SIZE;
	y *= TEX_SIZE;

	y = 1.f - y - TEX_SIZE;

	m_texCoords.push_back(glm::vec2(x, y));
	m_texCoords.push_back(glm::vec2(x, y + TEX_SIZE));
	m_texCoords.push_back(glm::vec2(x + TEX_SIZE, y));
	m_texCoords.push_back(glm::vec2(x + TEX_SIZE, y + TEX_SIZE));
}

BlockType* Chunk::GetBlock(const glm::i16vec3& pos) const {
	if (pos.x < 0||pos.x > CHUNK_WIDTH-1||
		pos.y < 0||pos.y > CHUNK_HEIGHT-1||
		pos.z < 0||pos.z > CHUNK_WIDTH-1) {
		return Blocks::BLOCK_TYPES[TYPE_AIR];
	}

	return m_map[pos.x][pos.y][pos.z].GetType();
}

uint16_t Chunk::GetBlockID(const glm::i16vec3& pos) const {
	if (pos.x<0||pos.x>=CHUNK_WIDTH||
		pos.y<0||pos.y>=CHUNK_HEIGHT||
		pos.z<0||pos.z>=CHUNK_WIDTH) {
		return TYPE_AIR;
	}

	return m_map[pos.x][pos.y][pos.z].GetTypeID();
}

uint16_t Chunk::GetBlockFromGlobalPos(const glm::ivec3& pos) const {
	int x = pos.x;
	int y = pos.y;
	int z = pos.z;

	x -= m_coord.x * CHUNK_WIDTH;
	z -= m_coord.y * CHUNK_WIDTH;

	if (x < 0 || x >= CHUNK_WIDTH || z < 0 || z >= CHUNK_WIDTH || y < 0 || y > CHUNK_HEIGHT) {
		return TYPE_AIR;
	}

	return m_map[x][y][z].GetTypeID();
}

ChunkCoord Chunk::GetChunkCoord() const {
	return m_coord;
}

glm::vec3 Chunk::GetGlobalPos(const glm::i16vec3& pos) const {
	return glm::vec3(pos.x+m_coord.x*CHUNK_WIDTH, pos.y, pos.z+m_coord.y*CHUNK_WIDTH);
}

bool Chunk::NeedUpdate() const {
	return m_update;
}

bool Chunk::NeedCreateMesh() const {
	return m_createMesh;
}