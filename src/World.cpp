#include <iostream>
#include "World.h"
#include "glm/gtc/noise.hpp"

World::World(const Camera& camera, GLFWwindow* p_window)
: mp_window(p_window), m_chunksUpdateThread(&World::UpdateChunks, this) {
	CheckViewDistance(camera, true);
}

World::~World(){
	// Stop the chunks update thread
	m_chunksUpdateThread.join();
		
	// Delete all chunk pointers
	for (auto& c : m_chunks) {
		delete c.second;
	}
}

void World::Draw(Shader& shader, const Camera& camera) {
	// Draw all chunks
	for (auto& c : m_chunks) {
		c.second->Draw(shader, camera);
	}
}

void World::Update() {
	for (auto& chunk : m_chunks) {
		if (chunk.second->NeedCreateMesh()) {
			chunk.second->CreateMesh();
		}
	}
}

void World::UpdateChunks() {
	// This is on other thread so while(true) won't lock up the main thread.
	while (!glfwWindowShouldClose(mp_window)) {
		for (auto& chunk : m_chunks) {
			if (chunk.second->NeedUpdate()) {
				chunk.second->Update();
			}
		}
	}
}

Chunk* World::RequestChunk(ChunkCoord coord, bool create) {
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

void World::CheckViewDistance(const Camera& camera, bool force) {
	ChunkCoord camCord = ChunkCoord::GetFromVec3(camera.GetPosition());
	
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

uint16_t World::GetBlock(int x, int y, int z) {
	if (y==0) { 
		return TYPE_BEDROCK; 
	}

	uint8_t height = GetHeight(x,z);

	if (y==height) {
		return TYPE_GRASS;
	} else if (y < height && y > height-4) {
		return TYPE_DIRT;
	} else if (y > height){
		return TYPE_AIR;
	} else {
		return TYPE_STONE;
	}

	return TYPE_AIR;
}

uint16_t World::GetBlock(glm::vec3 pos) {
	return GetBlock(pos.x, pos.y, pos.z);
}

uint8_t World::GetHeight(int x, int z) {
	// Get the noise value. 
	glm::vec2 pos(x*0.02f, z*0.02f);
	float height = glm::simplex(pos);

	// Make the height to be between 0.0 and 1.0. 
	height = (height+1)/2;

	// Make it bigger. 
	height *= 25;
	height += 60;

	return static_cast<uint8_t>(height);
}