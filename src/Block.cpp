#include "Block.h"
#include "BlocksContainer.h"
#include <iostream>

Block::Block(uint16_t type) {
	this->m_type = type;
}

void Block::SetType(uint16_t type) {
	this->m_type = type;
}

bool Block::IsSolid() const {
	return GetType()->IsSolid();
}

BlockType* Block::GetType() const {
	return Blocks::BLOCK_TYPES.at(m_type);
}

uint16_t Block::GetTypeID() const {
	return m_type;
}

uint16_t Block::GetTextureID(uint8_t face) const {
	switch (face) {
		case 0: return GetType()->m_backTex;
		case 1: return GetType()->m_frontTex;
		case 2: return GetType()->m_topTex;
		case 3: return GetType()->m_bottomTex;
		case 4: return GetType()->m_leftTex;
		case 5: return GetType()->m_rightTex;
	}
}