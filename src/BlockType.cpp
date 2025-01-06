#include "BlockType.h"
#include <iostream>
#include "Definitions.h"

BlockType::BlockType(const std::string name, const bool isSolid, const uint16_t top, const uint16_t bot, const uint16_t left, const uint16_t right, const uint16_t front, const uint16_t back){
	m_name = name;
	m_solid = isSolid;

	m_topTex = top;
	m_bottomTex = bot;
	m_leftTex = left;
	m_rightTex = right;
	m_frontTex = front;
	m_backTex = back;
}

std::string BlockType::GetName() const {
	return m_name;
}

bool BlockType::IsSolid() const {
	return m_solid;
}

bool BlockType::ShouldRenderNeighbours() const {
	return !m_solid;
}

