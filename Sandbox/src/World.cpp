#include "World.h"
#include <iostream>

World::World() {
	generate();
}

World::~World(){
	for (int i = 0; i<chunks.size(); i++) {
		delete chunks[i];
	}
}

void World::draw(Shader& shader, const Camera& camera) {
	for (int i = 0; i<chunks.size(); i++) {
		chunks[i]->draw(shader, camera);
	}
}

void World::generate() {
	for (int x = -16; x<16; x++) {
		for (int z = -16; z<16; z++) {
			chunks.push_back(new Chunk(ChunkCoord(x,z)));
		}
	}
}