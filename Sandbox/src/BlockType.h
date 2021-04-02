#pragma once

#include "core/Libs.h"
#include <string>

class BlockType {
public:
	BlockType(const std::string name, const bool isSolid, const uint16_t top=0, const uint16_t bot = 0, const uint16_t left = 0, uint16_t right = 0, const uint16_t front = 0, const uint16_t back = 0);

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
	uint16_t m_topTex=0;
	uint16_t m_bottomTex=0;
	uint16_t m_leftTex=0;
	uint16_t m_rightTex=0;
	uint16_t m_frontTex=0;
	uint16_t m_backTex=0;
};

