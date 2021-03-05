#pragma once

#include "Libs.h"
#include "core/Uv.h"

class BlockType {
public:
	BlockType(const bool isSolid, const UV& top, const UV& bot, const UV& left, const UV& right, const UV& front, const UV& back);

public:
	void calculateTexCoords();

public:
	bool m_isSolid;

	UV m_topTex;
	UV m_bottomTex;
	UV m_leftTex;
	UV m_rightTex;
	UV m_frontTex;
	UV m_backTex;
	
	UV m_texCoords[36]{};
};

