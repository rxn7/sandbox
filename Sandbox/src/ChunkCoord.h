#pragma once

#include "core/Libs.h"
#include "Definitions.h"

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

	inline static ChunkCoord fromPos(glm::vec3 pos){ return ChunkCoord((int)pos.x / CHUNK_WIDTH, (int)pos.z / CHUNK_WIDTH); }
	bool operator==(const ChunkCoord& other) { return x == other.x && y == other.y; }
	bool operator!=(const ChunkCoord& other) { return x != other.x || y != other.y; }
};

