#include "Block.h"

Block::Block(const uint16_t& type) {
	m_type = type;
}

void Block::setType(const uint16_t& type) {
	m_type = type;
}