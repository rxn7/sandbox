#pragma once

#include "BlockType.h"

#define TYPE_AIR 0
#define TYPE_GRASS 1
#define TYPE_DIRT 2
#define TYPE_COBBLESTONE 3
#define TYPE_STONE 4

namespace Blocks {
	static const BlockType AIR			("Air",				false);
	static const BlockType GRASS		("Grass",			true,  glm::vec2(1, 0), glm::vec2(2, 0), glm::vec2(0, 0), glm::vec2(0, 0), glm::vec2(0, 0), glm::vec2(0, 0));
	static const BlockType DIRT			("Dirt",			true,  glm::vec2(2, 0), glm::vec2(2, 0), glm::vec2(2, 0), glm::vec2(2, 0), glm::vec2(2, 0), glm::vec2(2, 0));
	static const BlockType COBBLESTONE	("Cobblestone",		true,  glm::vec2(0, 1), glm::vec2(0, 1), glm::vec2(0, 1), glm::vec2(0, 1), glm::vec2(0, 1), glm::vec2(0, 1));
	static const BlockType STONE        ("Stone",			true,  glm::vec2(1, 1), glm::vec2(1, 1), glm::vec2(1, 1), glm::vec2(1, 1), glm::vec2(1, 1), glm::vec2(1, 1));

	static const BlockType BLOCK_TYPES[] = {
		AIR,
		GRASS,
		DIRT,
		COBBLESTONE,
		STONE,
	};
}