#pragma once

#include <cstdint>
#include "BlockType.h"

class Block {
public:
	Block() {}
	Block(const uint16_t& type);

public:
	void setType(const uint16_t& type);
	inline uint16_t getType() { return m_type; }

private:
	uint16_t m_type{};
};