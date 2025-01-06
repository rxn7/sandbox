#pragma once

#include <mutex>
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
	void Update();

	/// <summary> Updates chunk mesh data for block at specified pos. </summary>
	void UpdateMeshData(const glm::i16vec3& pos);
	
	/// <summary> Creates the mesh. </summary>
	void CreateMesh();

	/// <summary> Adds the tex coords to the buffer. </summary>
	void AddTexture(uint16_t texID);
	
	/// <summary> Draws the mesh. </summary>
	void Draw(Shader& shader, const Camera& camera);
	
	/// <summary> Returns BlockType of block at the specified pos. </summary>
	BlockType* GetBlock(const glm::i16vec3& pos) const;

	/// <summary> Returns type of block at the specified GLOBAL pos. </summary>
	uint16_t GetBlockFromGlobalPos(const glm::ivec3& pos) const;

	/// <summary> Returns id of block at the specified pos. </summary>
	uint16_t GetBlockID(const glm::i16vec3& pos) const;

	/// <summary> Returns the m_coord. </summary>
	ChunkCoord GetChunkCoord() const;

	/// <summary> Returns global position of the specified local position.</summary>
	glm::vec3 GetGlobalPos(const glm::i16vec3& pos) const;
	
	/// <summary> Returns true if chunk needs updating. </summary>
	bool NeedUpdate() const;
	
	/// <summary> Returns true if chunk needs to create mesh. </summary>
	bool NeedCreateMesh() const;

private:
	/// <summary> Generates terrain. </summary>
	void GenerateTerrain();

	/// <summary> Clears the mesh buffer data. </summary>
	void ClearMeshData();

	/// <summary> Returns if this block is translucent / should its neighbours be rendered. </summary>
	bool ShouldRenderFace(const glm::i8vec3& pos);

public:
	Block m_map[CHUNK_WIDTH][CHUNK_HEIGHT][CHUNK_WIDTH];
	Mesh* mp_mesh;

private:
	bool m_createMesh;
	bool m_update;
	World* mp_world;
	ChunkCoord m_coord;

	std::vector<Vertex> m_vertices;
	std::vector<glm::vec3> m_verticesPositions;
	std::vector<GLuint> m_triangles;
	std::vector<glm::vec2> m_texCoords;

	GLuint m_vertexIndex = 0;
};