#include "World.h"
#include "Definitions.h"
#include "BlocksContainer.h"
#include "core/render/Shader.h"
#include <iostream>
#include "glm/gtc/noise.hpp"

Chunk::Chunk(World& world, ChunkCoord coord) {
	mp_world = &world;
	m_coord = coord;

	generateHeightMap();
	generateTerrain();
	update();
	createMesh();
}

Chunk::~Chunk() {
	delete mp_mesh;
}

void Chunk::generateTerrain() {
	for (int x = 0; x<CHUNK_WIDTH; x++) {
		for (int z = 0; z<CHUNK_WIDTH; z++) {
			int y = m_heightMap[x][z];
			m_map[x][y][z].setType(TYPE_GRASS);

			y--;
			for (; y>0; y--) {
				m_map[x][y][z].setType(TYPE_DIRT);
			}

			m_map[x][0][z].setType(TYPE_BEDROCK);
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
	mp_mesh->draw(camera, shader, m_coord);
}

BlockType* Chunk::getVoxel(const glm::i16vec3& pos) {
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

void Chunk::clearMeshData() {
	m_vertexIndex = 0;
	m_vertices.clear();
	m_triangles.clear();
	m_texCoords.clear();
}

bool Chunk::renderFace(const glm::i8vec3& pos) {
	if (pos.y < 0 || pos.y >= CHUNK_HEIGHT) {
		return true;
	}

	/* TODO: Optimize this. */
	if (pos.x < 0 || pos.x >= CHUNK_WIDTH || pos.z < 0 || pos.z >= CHUNK_WIDTH) {
		/*uint16_t t = mp_world->generateBlock(pos);
		return Blocks::BLOCK_TYPES[t]->renderNeighbours();*/

		return true;
	}

	return m_map[pos.x][pos.y][pos.z].getType()->renderNeighbours();
}

void Chunk::updateMeshData(const glm::i16vec3& pos) {
	if (getVoxelID(pos) == TYPE_AIR) return;
	
	for (uint8_t f = 0; f<6; f++) { /* Each block has 6 faces */
		if (renderFace(pos + FACES[f])) {
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

void Chunk::generateHeightMap() {
	for (uint8_t x = 0; x<CHUNK_WIDTH; x++) {
		for (uint8_t z = 0; z<CHUNK_WIDTH; z++) {
			int blockX = x + m_coord.x * CHUNK_WIDTH;
			int blockZ = z + m_coord.y * CHUNK_WIDTH;

			
			/* Get noise value. */
			float value = glm::simplex(glm::vec2(blockX / 32.0f, blockZ / 32.0f));

			/* Make the height to be between 0.0 and 1.0. */
			value = (value+1)/2;

			/* Make it bigger. */
			value *= 16 + 16;

			m_heightMap[x][z] = static_cast<int>(value);
		}
	}
}