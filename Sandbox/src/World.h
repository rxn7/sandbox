#pragma once

#include "Chunk.h"
#include <unordered_map>

class World {
public:
	World(const Camera& camera);
	virtual ~World();

public:
	/// <summary> Calls draw() on all the chunks. </summary>
	void draw(Shader& shader, const Camera& camera);
	
	/// <summary> Generates and returns block type at specified position. </summary>
	uint16_t generateBlock(glm::ivec3 pos);

	/// <summary> Returns chunk at specified coord if exits. Else if create is true it creates new chunk. </summary>
	Chunk* requestChunk(ChunkCoord coord, bool create = false);

	void checkViewDistance(const Camera& camera, bool force=false);

public:
	std::unordered_map<ChunkCoord, Chunk*> m_chunks;

private:
	ChunkCoord lastCamCoord;
};

