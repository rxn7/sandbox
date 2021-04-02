#pragma once

#include <unordered_map>
#include <thread>
#include "Chunk.h"

class World {
public:
	World(const Camera& camera);
	virtual ~World();

public:
	/// <summary> Calls draw() on all the chunks. </summary>
	void draw(Shader& shader, const Camera& camera);
	
	void update();

	/// <summary> Returns chunk at specified coord if exits. Else if create is true it creates new chunk. </summary>
	Chunk* requestChunk(ChunkCoord coord, bool create = false);

	/// <summary> Deletes/creates new chunks if neeedd. </summary>
	void checkViewDistance(const Camera& camera, bool force=false);

	/// <summary> Returns block type at specified pos. </summary>
	BlockType* getBlock(const glm::vec3 pos);

private:
	/// <summary> Function for m_chunksUpdateThread thread. </summary>
	void updateChunks();

public:
	std::unordered_map<ChunkCoord, Chunk*> m_chunks;

private:
	std::mutex m_chunksListLock;
	std::thread m_chunksUpdateThread;
	ChunkCoord m_lastCamCoord;
};

