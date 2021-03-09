#include "Block.h"
#include "BlocksContainer.cpp"
#include <iostream>

Block::Block(uint16_t type) {
	this->m_type = type;
}

void Block::setType(uint16_t type) {
	this->m_type = type;
}

glm::vec2 Block::getTextureCoord(uint8_t face) {
	switch (face) {
		case 0: return getType().m_backTex;
		case 1: return getType().m_frontTex;
		case 2: return getType().m_topTex;
		case 3: return getType().m_bottomTex;
		case 4: return getType().m_leftTex;
		case 5: return getType().m_rightTex;
	}
}