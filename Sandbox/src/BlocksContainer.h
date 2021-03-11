#pragma once

#include "BlockType.h"
#include <vector>

#define TYPE_AIR 0
#define TYPE_GRASS 1
#define TYPE_DIRT 2
#define TYPE_COBBLESTONE 3
#define TYPE_STONE 4
#define TYPE_BRICKS 5
#define TYPE_BEDROCK 6
#define TYPE_OAK_LOG 7
#define TYPE_GOLD_BLOCK 8
#define TYPE_DIORITE 9
#define TYPE_OBSIDIAN 10
#define TYPE_OAK_PLANKS 11

namespace Blocks {
	static const std::vector<BlockType*> BLOCK_TYPES = {
		new BlockType("Air", false),
		new BlockType("Grass", true, 1, 2, 0, 0, 0, 0),
		new BlockType("Dirt", true, 2, 2, 2, 2, 2, 2),
		new BlockType("Cobblestone", true, 3, 3, 3, 3, 3, 3),
		new BlockType("Stone", true, 4, 4, 4, 4, 4, 4),
		new BlockType("Bricks", true, 5, 5, 5, 5, 5, 5),
		new BlockType("Bedrock", true, 6, 6, 6, 6, 6, 6),
		new BlockType("Oak Log", true, 8, 8, 7, 7, 7, 7),
		new BlockType("Gold Block", true, 9, 9, 9, 9, 9, 9),
		new BlockType("Diorite", true, 10, 10, 10, 10, 10, 10),
		new BlockType("Obsidian", true, 11, 11, 11, 11, 11, 11),
		new BlockType("Oak Planks", true, 12, 12, 12, 12, 12, 12),
	};

	static void clearArray(){
		for (auto b : BLOCK_TYPES) {
			delete b;
		}
	}
}