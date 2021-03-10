#pragma once
#include <vector>
#include "Chunk.h"
#include <unordered_map>

class World {
public:
	World();
	virtual ~World();

public:
	/// <summary> Generates the world. </summary>
	void generate();

	/// <summary> Calls draw() on all the chunks. </summary>
	void draw(Shader& shader, const Camera& camera);
	
	/// <summary> Returns block type at specified position. </summary>
	uint8_t getBlock(glm::ivec3 pos);

public:
	std::vector<Chunk*> m_chunks;
};

