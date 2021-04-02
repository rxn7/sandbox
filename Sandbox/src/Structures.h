#pragma once

namespace Structures {
	void genTree(Chunk* chunk, uint16_t x, uint8_t y, uint16_t z) {
		int _y = y+1;

		for (; _y<y+4; _y++) {
			chunk->m_map[x][_y][z].setType(TYPE_OAK_LOG);
		}

		chunk->m_map[x][_y-1][z].setType(TYPE_OAK_LEAVES);
	}
}