#pragma once

#include "BlockType.h"
#include "BlocksContainer.cpp"

struct Block {
public:
	Block() {}
	Block(uint16_t type);
public:
	void setType(uint16_t type);
	inline bool solid() { return getType().solid(); }
	inline BlockType getType() { return Blocks::BLOCK_TYPES[m_type]; }
	inline uint16_t getTypeID() { return m_type; }
	glm::vec2 getTexture(uint8_t face);

private:
	uint16_t m_type = 0;
};