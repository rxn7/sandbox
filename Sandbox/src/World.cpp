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
			m_chunks.push_back(new Chunk(*this, ChunkCoord(x, z)));
		}
	}
}

uint16_t World::getBlock(glm::ivec3 pos) {
	if (pos.y == 0) return TYPE_BEDROCK;
	
	uint16_t typeValue=0;

	if (pos.y == CHUNK_HEIGHT-1)								    typeValue = TYPE_GRASS;
	else if (pos.y < CHUNK_HEIGHT-1 && pos.y > CHUNK_HEIGHT-3)    typeValue = TYPE_DIRT;
	else if (pos.y <= CHUNK_HEIGHT -3)						    typeValue = TYPE_STONE;
	else if (pos.y > CHUNK_HEIGHT) return 0;

	return typeValue;
}