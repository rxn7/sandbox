#include <iostream>
#include "World.h"
#include "glm/gtc/noise.hpp"

World::World(const Camera& camera, GLFWwindow* p_window)
: mp_window(p_window), m_chunksUpdateThread(&World::updateChunks, this) {
	checkViewDistance(camera, true);
}

World::~World(){
	// Stop the chunks update thread
	m_chunksUpdateThread.join();
		
	// Delete all chunk pointers
	for (auto& c : m_chunks) {
		delete c.second;
	}
}

void World::draw(Shader& shader, const Camera& camera) {
	// Draw all chunks
	for (auto& c : m_chunks) {
		c.second->draw(shader, camera);
	}
}

void World::update() {
	for (auto& chunk : m_chunks) {
		if (chunk.second->needCreateMesh()) {
			chunk.second->createMesh();
		}
	}
}

void World::updateChunks() {
	// This is on other thread so while(true) won't lock up the main thread.
	while (!glfwWindowShouldClose(mp_window)) {
		for (auto& chunk : m_chunks) {
			if (chunk.second->needUpdate()) {
				chunk.second->update();
			}
		}
	}
}

Chunk* World::requestChunk(ChunkCoord coord, bool create) {
	if (m_chunks.count(coord)) {
		return m_chunks[coord];
	} else {
		// If chunk doesn't exist and user doesn't want to create it - return nullptr.
		if (!create) {
			return nullptr;
		} 
		// If chunk doesn't exist and user wants to create it - create new one.
		else {
			Chunk* c = new Chunk(*this, coord);
			m_chunks[coord] = c;
			return c;
		}
	}
}

void World::checkViewDistance(const Camera& camera, bool force) {
	ChunkCoord camCord = ChunkCoord::getFromVec3(camera.getPosition());
	
	if (camCord == m_lastCamCoord && !force) {
		m_lastCamCoord = camCord;
		return;
	}
	m_lastCamCoord = camCord;

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