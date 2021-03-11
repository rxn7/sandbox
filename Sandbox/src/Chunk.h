#pragma once

#include <memory>
#include <vector>
#include "core/Libs.h"
#include "core/render/Mesh.h"
#include "Block.h"
#include "Definitions.h"

class World;

class Chunk {
public:
	Chunk(World& world, ChunkCoord coord);
	virtual ~Chunk();

public:
	/// <summary> Updates the chunk mesh data for each block. </summary>
	void update();

	/// <summary> Updates chunk mesh data for block at specified pos. </summary>
	void updateMeshData(const glm::i16vec3& pos);
	
	/// <summary> Creates the mesh. </summary>
	void createMesh();

	/// <summary> Adds the tex coords to the buffer. </summary>
	void addTexture(uint16_t texID);
	
	/// <summary> Draws the mesh. </summary>
	void draw(Shader& shader, const Camera& camera);
	
	/// <summary> Returns BlockType of block at the specified pos. </summary>
	BlockType* getVoxel(const glm::i16vec3& pos);

	/// <summary> Returns id of block at the specified pos. </summary>
	uint16_t getVoxelID(const glm::i16vec3& pos);

	/// <summary> Returns the m_coord. </summary>
	inline ChunkCoord getChunkCoord() const { return m_coord; }

	void generateHeightMap();

private:
	/// <summary> Generates terrain. </summary>
	void generateTerrain();

	/// <summary> Clears the mesh buffer data. </summary>
	void clearMeshData();

	/// <summary> Returns if this block is translucent / should its neighbours be rendered. </summary>
	bool renderFace(const glm::i8vec3& pos);

public:
	Block m_map[CHUNK_WIDTH][CHUNK_HEIGHT][CHUNK_WIDTH];
	Mesh* mp_mesh;

private:
	World* mp_world;
	ChunkCoord m_coord;

	int m_heightMap[CHUNK_WIDTH][CHUNK_WIDTH];
	std::vector<glm::vec3> m_vertices;
	std::vector<GLuint> m_triangles;
	std::vector<glm::vec2> m_texCoords;

	GLuint m_vertexIndex = 0;
};