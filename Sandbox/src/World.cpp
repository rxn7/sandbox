#include "World.h"
#include <iostream>
#include "glm/gtc/noise.hpp"

World::World(const Camera& camera) {
	checkViewDistance(camera, true);
}

World::~World(){
	for (auto& c : m_chunks) {
		delete c.second;
	}
}

void World::draw(Shader& shader, const Camera& camera) {
	for (auto& c : m_chunks) {
		c.second->draw(shader, camera);
	}
}

Chunk* World::requestChunk(ChunkCoord coord, bool create) {
	if (m_chunks.count(coord)) {
		return m_chunks[coord];
	} else {
		if (!create) {
			return nullptr;
		} else {
			m_chunks[coord] = new Chunk(*this, coord);
			return m_chunks[coord];
		}
	}
}

void World::checkViewDistance(const Camera& camera, bool force) {
	ChunkCoord camCord = ChunkCoord::getFromVec3(camera.getPosition());
	
	if (camCord == lastCamCoord && !force) {
		lastCamCoord = camCord;
		return;
	}
	lastCamCoord = camCord;

	/* Copy each key from m_chunks to new vector. Then remove from this vector chunks that have to stay. */
	std::vector<ChunkCoord> chunksToRemove{};
	for (auto& c : m_chunks) {
		chunksToRemove.push_back(c.first);
	}
	
	for (int x = camCord.x - VIEW_DISTANCE; x < camCord.x + VIEW_DISTANCE; x++) {
		for (int y = camCord.y - VIEW_DISTANCE; y < camCord.y + VIEW_DISTANCE; y++) {
			ChunkCoord c(x,y);
			/* If there is no chunk at this coord, create new one. */
			if (m_chunks.count(c) == 0) {
				m_chunks.insert({c, new Chunk(*this, c)});
			} 

			/* Don't remove this chunk. */
			for (int i = 0; i<chunksToRemove.size(); i++) {
				if (chunksToRemove[i] == c) {
					chunksToRemove.erase(chunksToRemove.begin() + i);
				}
			}
		}
	}

	/* Remove each chunk from m_chunks that is in chunksToRemove vector. */
	for (auto& c : chunksToRemove) {
		delete m_chunks[c];
		m_chunks.erase(c);
	}
}

/*TODO:*/
BlockType* World::getBlock(const glm::vec3 pos) {
	ChunkCoord coord(pos.x / (CHUNK_WIDTH), pos.z / (CHUNK_WIDTH));
	Chunk* chunk = requestChunk(coord);

	if (!chunk) { return TYPE_AIR; }
	
	return Blocks::BLOCK_TYPES[chunk->getBlockFromGlobalPos(pos)];
}