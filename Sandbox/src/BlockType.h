#pragma once

#include "core/Libs.h"
#include <string>

class BlockType {
public:
	BlockType(const std::string name, const bool isSolid, const uint16_t top=0, const uint16_t bot = 0, const uint16_t left = 0, uint16_t right = 0, const uint16_t front = 0, const uint16_t back = 0);

public:
	/// <summary> Returns the name of the block type. </summary>
	std::string GetName() const;

	/// <summary> Returns true if block should render its neighbours. </summary>
	bool ShouldRenderNeighbours() const;

	/// <summary> Returns true if block is solid. </summary>
	bool IsSolid() const;

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

