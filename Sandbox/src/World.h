#pragma once
#include <vector>
#include "Chunk.h"
#include <unordered_map>

class World {
public:
	World();
	virtual ~World();

public:
	void generate();
	void draw(Shader& shader, const Camera& camera);
	
public:
	std::vector<Chunk*> m_chunks;
};

