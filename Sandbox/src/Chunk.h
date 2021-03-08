#pragma once

#include <vector>
#include "core/Libs.h"
#include "core/render/Mesh.h"
#include "ChunkCoord.h"
#include "Block.h"
#include "core/Definitions.h"

class Chunk {
public:
	Chunk(ChunkCoord coord);
	~Chunk();

public:
	//void getVoxelFromGlobalPos(glm::vec3 pos);
	//void updateChunk();
	void update();
	void updateMeshData(const glm::i16vec3& pos);
	void createMesh();
	void addTexture(const glm::vec2& texPos);
	void draw(Shader& shader, const Camera& camera);
	BlockType getVoxel(const glm::i16vec3& pos);
	uint16_t getVoxelID(const glm::i16vec3& pos);
	inline ChunkCoord getChunkCoord() const { return m_coord; }

private:
	void generateTerrain();
	void clearMeshData();

public:
	Block m_map[CHUNK_WIDTH][CHUNK_HEIGHT][CHUNK_WIDTH];

private:
	Mesh* mp_mesh;
	ChunkCoord m_coord;

	std::vector<glm::vec3> m_vertices;
	std::vector<GLuint> m_triangles;
	std::vector<glm::vec2> m_texCoords;

	GLuint m_vertexIndex = 0;
};