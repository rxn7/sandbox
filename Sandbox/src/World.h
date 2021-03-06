#pragma once
#include <vector>
#include "Chunk.h"

class World {
public:
	World();
	virtual ~World();

public:
	void generate();
	void draw(Shader& shader, const Camera& camera);

public:
	std::vector<Chunk*> chunks;
};

