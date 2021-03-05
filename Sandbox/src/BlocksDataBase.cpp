#pragma once

#include "BlockType.h"

namespace Vertices {
	static const glm::vec3 blockVertices[36] = {
		// Front
		glm::vec3(-1, -1, -1),
		glm::vec3(-1, 1, -1),
		glm::vec3(1, 1, -1),

		glm::vec3(1, 1, -1),
		glm::vec3(1, -1, -1),
		glm::vec3(-1, -1, -1),

		// Back
		glm::vec3(1, 1, 1),
		glm::vec3(-1, 1, 1),
		glm::vec3(-1, -1, 1),

		glm::vec3(-1, -1, 1),
		glm::vec3(1, -1, 1),
		glm::vec3(1, 1, 1),

		// Left
		glm::vec3(-1, 1, 1),
		glm::vec3(-1, 1, -1),
		glm::vec3(-1, -1, 1),

		glm::vec3(-1, 1, -1),
		glm::vec3(-1, -1, -1),
		glm::vec3(-1, -1, 1),

		// Right
		glm::vec3(1, 1, -1),
		glm::vec3(1, 1, 1),
		glm::vec3(1, -1, 1),

		glm::vec3(1, -1, 1),
		glm::vec3(1, -1, -1),
		glm::vec3(1, 1, -1),

		// Top
		glm::vec3(-1, 1, -1),
		glm::vec3(-1, 1, 1),
		glm::vec3(1, 1, 1),

		glm::vec3(1, 1, 1),
		glm::vec3(1, 1, -1),
		glm::vec3(-1, 1, -1),

		// Bottom
		glm::vec3(-1, -1, 1),
		glm::vec3(-1, -1, -1),
		glm::vec3(1, -1, -1),

		glm::vec3(1, -1, -1),
		glm::vec3(1, -1, 1),
		glm::vec3(-1, -1, 1),
	};
}

namespace BlocksDB {
	static const BlockType GRASS		(true, UV(1, 0), UV(2, 0), UV(0, 0), UV(0, 0), UV(0, 0), UV(0, 0));
	static const BlockType DIRT			(true, UV(2, 0), UV(2, 0), UV(2, 0), UV(2, 0), UV(2, 0), UV(2, 0));
	static const BlockType COBBLESTONE	(true, UV(0, 1), UV(0, 1), UV(0, 1), UV(0, 1), UV(0, 1), UV(0, 1));
	static const BlockType STONE        (true, UV(1, 1), UV(1, 1), UV(1, 1), UV(1, 1), UV(1, 1), UV(1, 1));

	static const BlockType BLOCK_TYPES[] = {
		GRASS,
		DIRT,
		COBBLESTONE,
		STONE,
	};
}