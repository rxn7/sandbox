#include "BlockType.h"
#include <iostream>

#define ATLAS_COLUMNS 3
#define ATLAS_ROWS 2

const static float TEX_WIDTH = 1.f / (float)ATLAS_COLUMNS;
const static float TEX_HEIGHT = 1.f / (float)ATLAS_ROWS;

BlockType::BlockType(const bool isSolid, const UV& top, const UV& bot, const UV& left, const UV& right, const UV& front, const UV& back){
	m_isSolid = isSolid;

	m_topTex = top;
	m_bottomTex = bot;
	m_leftTex = left;
	m_rightTex = right;

	m_frontTex = front;
	m_backTex = back;
	
	calculateTexCoords();
}

void BlockType::calculateTexCoords() {
	// Front
	float frontW = TEX_WIDTH*m_frontTex.x;
	float frontH = TEX_HEIGHT*m_frontTex.y;

	m_texCoords[0] = UV(frontW, frontH - TEX_HEIGHT);
	m_texCoords[1] = UV(frontW, frontH);
	m_texCoords[2] = UV(frontW + TEX_WIDTH, frontH);
	
	m_texCoords[3] = UV(frontW + TEX_WIDTH, frontH);
	m_texCoords[4] = UV(frontW + TEX_WIDTH, frontH - TEX_HEIGHT);
	m_texCoords[5] = UV(frontW, frontH - TEX_HEIGHT);
	
	// Back
	float backW = TEX_WIDTH*m_backTex.x;
	float backH = TEX_HEIGHT*m_backTex.y;

	m_texCoords[6] = UV(backW + TEX_WIDTH, backH);
	m_texCoords[7] = UV(backW, backH);
	m_texCoords[8] = UV(backW, backH - TEX_HEIGHT);

	m_texCoords[9] = UV(backW, backH - TEX_HEIGHT);
	m_texCoords[10] = UV(backW + TEX_WIDTH, backH - TEX_HEIGHT);
	m_texCoords[11] = UV(backW + TEX_WIDTH, backH);
	
	// Left
	float leftW = TEX_WIDTH*m_leftTex.x;
	float leftH = TEX_HEIGHT*m_leftTex.y;

	m_texCoords[12] = UV(leftW, leftH);
	m_texCoords[13] = UV(leftW + TEX_WIDTH, leftH);
	m_texCoords[14] = UV(leftW, leftH - TEX_HEIGHT);
	 
	m_texCoords[15] = UV(leftW + TEX_WIDTH, leftH);
	m_texCoords[16] = UV(leftW + TEX_WIDTH, leftH - TEX_HEIGHT);
	m_texCoords[17] = UV(leftW, leftH - TEX_HEIGHT);
	
	// Right
	float rightW = TEX_WIDTH*m_rightTex.x;
	float rightH = TEX_HEIGHT*m_rightTex.y;

	m_texCoords[18] = UV(rightW + TEX_WIDTH, rightH);
	m_texCoords[19] = UV(rightW, rightH);
	m_texCoords[20] = UV(rightW, rightH - TEX_HEIGHT);

	m_texCoords[21] = UV(rightW, rightH - TEX_HEIGHT);
	m_texCoords[22] = UV(rightW + TEX_WIDTH, rightH - TEX_HEIGHT);
	m_texCoords[23] = UV(rightW + TEX_WIDTH, rightH);

	// Top
	float topW = TEX_WIDTH*m_topTex.x;
	float topH = TEX_HEIGHT*m_topTex.y;

	m_texCoords[24] = UV(topW, topH - TEX_HEIGHT);
	m_texCoords[25] = UV(topW, topH);
	m_texCoords[26] = UV(topW + TEX_WIDTH, topH);

	m_texCoords[27] = UV(topW + TEX_WIDTH, topH);
	m_texCoords[28] = UV(topW + TEX_WIDTH, topH - TEX_HEIGHT);
	m_texCoords[29] = UV(topW, topH - TEX_HEIGHT);

	// Bottom
	float botW = TEX_WIDTH*m_bottomTex.x;
	float botH = TEX_HEIGHT*m_bottomTex.y;

	m_texCoords[30] = UV(botW, botH - TEX_HEIGHT);
	m_texCoords[31] = UV(botW, botH);
	m_texCoords[32] = UV(botW + TEX_WIDTH, botH);
	
	m_texCoords[33] = UV(botW + TEX_WIDTH, botH);
	m_texCoords[34] = UV(botW, botH);
	m_texCoords[35] = UV(botW, botH - TEX_HEIGHT);
}