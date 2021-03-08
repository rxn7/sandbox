#include "BlockType.h"
#include <iostream>
#include "core/Definitions.h"

BlockType::BlockType(const std::string name, const bool isSolid, const glm::vec2& top, const glm::vec2& bot, const glm::vec2& left, const glm::vec2& right, const glm::vec2& front, const glm::vec2& back){
	m_name = name;
	m_solid = isSolid;

	m_topTex = top;
	m_bottomTex = bot;
	m_leftTex = left;
	m_rightTex = right;
	m_frontTex = front;
	m_backTex = back;
}