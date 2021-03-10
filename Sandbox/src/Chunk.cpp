#include "World.h"
#include "Definitions.h"
#include "BlocksContainer.cpp"
#include "core/render/Shader.h"
#include <iostream>

Chunk::Chunk(World& world, ChunkCoord coord) {
	m_coord = coord;
	generateTerrain(world);
	update();
	createMesh();
}

void Chunk::generateTerrain(World& world) {
	for (int x = 0; x<CHUNK_WIDTH; x++) {
		for (int z = 0; z<CHUNK_WIDTH; z++) {
			for (int y = 0; y<CHUNK_HEIGHT; y++) {
				m_map[x][y][z].setType(world.getBlock(glm::vec3(x,y,z)));
			}
		}
	}
}

void Chunk::update() {
	for (int x = 0; x<CHUNK_WIDTH; x++) {
		for (int y = 0; y<CHUNK_HEIGHT; y++) {
			for (int z = 0; z<CHUNK_WIDTH; z++) {
				updateMeshData(glm::i16vec3(x, y, z));
			}
		}
	}
}

void Chunk::draw(Shader& shader, const Camera& camera) {
	if (mp_mesh != nullptr) mp_mesh->draw(camera, shader);
}

BlockType Chunk::getVoxel(const glm::i16vec3& pos) {
	if (pos.x < 0 || pos.x > CHUNK_WIDTH-1 ||
		pos.y < 0 || pos.y > CHUNK_HEIGHT-1 ||
		pos.z < 0 || pos.z > CHUNK_WIDTH-1) {
		return Blocks::BLOCK_TYPES[TYPE_AIR];
	}

	return m_map[pos.x][pos.y][pos.z].getType();
}

uint16_t Chunk::getVoxelID(const glm::i16vec3& pos) {
	if (pos.x < 0 || pos.x >= CHUNK_WIDTH ||
		pos.y < 0 || pos.y >= CHUNK_HEIGHT ||
		pos.z < 0 || pos.z >= CHUNK_WIDTH) {
		return TYPE_AIR;
	}

	return m_map[pos.x][pos.y][pos.z].getTypeID();
}

Chunk::~Chunk() {
	delete mp_mesh;
}

void Chunk::clearMeshData() {
	m_vertexIndex = 0;
	m_vertices.clear();
	m_triangles.clear();
	m_texCoords.clear();
}

void Chunk::updateMeshData(const glm::i16vec3& pos) {
	if (getVoxelID(pos) == TYPE_AIR) return;
	
	for (uint8_t f = 0; f<6; f++) { /* Each block has 6 faces */
		if (getVoxel(pos + FACES[f]).renderNeighbours()) {
			Block& block = m_map[pos.x][pos.y][pos.z];

			for (int i = 0; i<4; i++) {	/* Each face has 4 vertices */
				m_vertices.push_back(pos + VERTICES[TRIANGLES[f][i]]);
			}
			
			addTexture(block.getTextureID(f));

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

void Chunk::createMesh() {
	std::vector<Vertex> vertices;

	for (size_t i = 0; i<m_vertices.size(); i++) {
		vertices.push_back(Vertex(m_vertices[i], m_texCoords[i]));
	}

	mp_mesh = new Mesh(vertices, m_triangles);
	mp_mesh->getTransform()->setPos(glm::vec3(m_coord.x * CHUNK_WIDTH, 0, m_coord.y * CHUNK_WIDTH));
}

void Chunk::addTexture(uint16_t texID) {
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