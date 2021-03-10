#pragma once

#include <vector>
#include "core/Libs.h"
#include "core/render/Mesh.h"
#include "ChunkCoord.h"
#include "Block.h"
#include "Definitions.h"

class World;

class Chunk {
public:
	Chunk(World& world, ChunkCoord coord);
	~Chunk();

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
	BlockType getVoxel(const glm::i16vec3& pos);

	/// <summary> Returns id of block at the specified pos. </summary>
	uint16_t getVoxelID(const glm::i16vec3& pos);

	/// <summary> Returns the m_coord. </summary>
	inline ChunkCoord getChunkCoord() const { return m_coord; }

private:
	/// <summary> Generates terrain. </summary>
	void generateTerrain(World& world);

	/// <summary> Clears the mesh buffer data. </summary>
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