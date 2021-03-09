#pragma once

#include "core/Libs.h"
#include <string>

class BlockType {
public:
	BlockType(const std::string name, const bool isSolid, const glm::vec2& top=glm::vec2(), const glm::vec2& bot = glm::vec2(), const glm::vec2& left = glm::vec2(), const glm::vec2& right = glm::vec2(), const glm::vec2& front = glm::vec2(), const glm::vec2& back = glm::vec2());

public:
	/// <summary> Returns the m_name. </summary>
	inline std::string getName() const { return m_name;  }

	/// <summary> Returns the !m_solid. </summary>
	inline bool renderNeighbours() const { return !m_solid; }

	/// <summary> Returns the m_solid. </summary>
	inline bool solid() const { return m_solid; }

private:
	std::string m_name;
	bool m_solid;

public:
	glm::vec2 m_topTex;
	glm::vec2 m_bottomTex;
	glm::vec2 m_leftTex;
	glm::vec2 m_rightTex;
	glm::vec2 m_frontTex;
	glm::vec2 m_backTex;
};

