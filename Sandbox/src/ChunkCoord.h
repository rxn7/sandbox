#pragma once

#include "core/Libs.h"

struct ChunkCoord {
	int32_t x, y;

	ChunkCoord() {
		x = 0;
		y = 0;
	}

	ChunkCoord(int32_t x, int32_t y) {
		this->x = x;
		this->y = y;
	}
};

