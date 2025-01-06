#pragma once
#include "Libs.h"
#include "../Definitions.h"

struct ChunkCoord {
	int x, y;

	ChunkCoord(int x, int y) {
		this->x = x;
		this->y = y;
	}

	ChunkCoord() {
		x = 0;
		y = 0;
	}

	static ChunkCoord GetFromVec3(glm::vec3 pos) {
		int x = static_cast<int>(floor(pos.x)) / CHUNK_WIDTH;
		int y = static_cast<int>(floor(pos.z)) / CHUNK_WIDTH;

		return ChunkCoord(x, y);
	}

	bool operator==(const ChunkCoord& other) const {
		return (x == other.x && y == other.y);
	}
};

namespace std {
	template<> struct hash<ChunkCoord> {
		std::size_t operator()(ChunkCoord const& c) const noexcept {
			return std::hash<std::string>{}(std::to_string(c.x) + std::to_string(c.y));
		}
	};
}
