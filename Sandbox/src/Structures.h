#pragma once

namespace Structures {
	void genTree(Chunk* chunk, uint16_t x, uint8_t y, uint16_t z) {
		int _y = y;
		for (; y<_y+3; y++) {
			chunk->m_map[x][y][z].setType(TYPE_OAK_LOG);
		}
	}
}