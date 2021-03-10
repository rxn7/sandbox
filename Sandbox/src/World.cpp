#include "World.h"
#include <iostream>

World::World() {
	generate();
}

World::~World(){
	for (size_t i = 0; i<m_chunks.size(); i++) {
		delete m_chunks[i];
	}
}

void World::draw(Shader& shader, const Camera& camera) {
	for (size_t i = 0; i<m_chunks.size(); i++) {
		m_chunks[i]->draw(shader, camera);
	}
}

void World::generate() {
	srand(time(NULL));
	for (int x = -9; x<9; x++) {
		for (int z = -9; z<9; z++) {
			m_chunks.push_back(new Chunk(ChunkCoord(x, z)));
		}
	}
}

uint8_t getBlock(glm::ivec3 pos) {
	return 0;
}