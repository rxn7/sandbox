#include "World.h"
#include <iostream>

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

uint16_t World::generateBlock(glm::ivec3 pos) {
	if (pos.y == 0) return TYPE_BEDROCK;
	
	uint16_t typeValue=0;
	
	if (pos.y == CHUNK_HEIGHT-1)								  typeValue = TYPE_GRASS;
	else if (pos.y < CHUNK_HEIGHT-1 && pos.y > CHUNK_HEIGHT-3)    typeValue = TYPE_DIRT;
	else if (pos.y <= CHUNK_HEIGHT -3)						      typeValue = TYPE_STONE;
	else if (pos.y > CHUNK_HEIGHT) return TYPE_AIR;				

	return typeValue;
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

/* TODO: !Optimize this! */
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
			if (!m_chunks.count(c)) {
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
	/* TODO: Memory leak */
	for (auto c : chunksToRemove) {
		delete m_chunks[c];
		m_chunks.erase(c);
	}
}