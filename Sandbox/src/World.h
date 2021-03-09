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
	
public:
	std::vector<Chunk*> m_chunks;
};

