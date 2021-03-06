#pragma once

#include "core/Libs.h"
#include <string>

class BlockType {
public:
	BlockType(const std::string name, const bool isSolid, const glm::vec2& top=glm::vec2(), const glm::vec2& bot = glm::vec2(), const glm::vec2& left = glm::vec2(), const glm::vec2& right = glm::vec2(), const glm::vec2& front = glm::vec2(), const glm::vec2& back = glm::vec2());

public:
	inline std::string getName() const { return m_name;  }
	inline bool isTranslucent() const { return !m_isSolid; }

private:
	std::string m_name;
	bool m_isSolid;

public:
	glm::vec2 m_topTex;
	glm::vec2 m_bottomTex;
	glm::vec2 m_leftTex;
	glm::vec2 m_rightTex;
	glm::vec2 m_frontTex;
	glm::vec2 m_backTex;
};

