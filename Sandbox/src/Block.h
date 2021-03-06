#pragma once

#include "BlockType.h"
#include "BlocksContainer.cpp"

struct Block {
public:
	Block() {}
	Block(uint16_t type);
public:
	void setType(uint16_t type);
	inline BlockType getType() { return Blocks::BLOCK_TYPES[type]; }
	glm::vec2 getTexture(uint8_t face);

private:
	uint16_t type = 0;
};