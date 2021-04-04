#pragma once

#include <unordered_map>
#include <thread>
#include "Chunk.h"

class World {
public:
	World(const Camera& camera, GLFWwindow* p_window);
	virtual ~World();

public:
	/// <summary> Calls draw() on all the chunks. </summary>
	void Draw(Shader& shader, const Camera& camera);
	
	void Update();

	/// <summary> Returns chunk at specified coord if exits. Else if create is true it creates new chunk. </summary>
	Chunk* RequestChunk(ChunkCoord coord, bool create = false);

	/// <summary> Deletes/creates new chunks if neeedd. </summary>
	void CheckViewDistance(const Camera& camera, bool force=false);

	/// <summary> Returns block type at specified pos. </summary>
	BlockType* GetBlock(const glm::vec3 pos);

private:
	/// <summary> NOTE: This is on m_chunksUpdateThread!
	/// Updates chunks if needed. </summary>
	void UpdateChunks();

public:
	std::unordered_map<ChunkCoord, Chunk*> m_chunks;

private:
	GLFWwindow* mp_window;

	std::thread m_chunksUpdateThread;
	ChunkCoord m_lastCamCoord;
};

