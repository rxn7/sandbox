#pragma once

#include "Libs.h"

typedef unsigned int uint;

class BlockType {
public:
	BlockType(uint t, uint b, uint l, uint r, uint f, uint ba);
	~BlockType();

private:
	static uint topTex;
	static uint bottomText;
	static uint leftText;
	static uint rightText;
	static uint frontText;
	static uint backText;
	
	static glm::vec2 texCoords[36];
};

