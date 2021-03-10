#pragma once

#include "BlockType.h"

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
	static const BlockType AIR			("Air",				false);
	static const BlockType GRASS		("Grass",			true,  1,2,0,0,0,0);
	static const BlockType DIRT			("Dirt",			true,  2,2,2,2,2,2);
	static const BlockType COBBLESTONE	("Cobblestone",		true,  3,3,3,3,3,3);
	static const BlockType STONE        ("Stone",			true,  4,4,4,4,4,4);
	static const BlockType BRICKS       ("Bricks",			true,  5,5,5,5,5,5);
	static const BlockType BEDROCK      ("Bedrock",			true,  6,6,6,6,6,6);
	static const BlockType OAK_LOG      ("Oak Log",			true,  8,8,7,7,7,7);
	static const BlockType GOLD_BLOCK   ("Gold Block",		true,  9,9,9,9,9,9);
	static const BlockType DIORITE		("Diorite",			true,  10,10,10,10,10,10);
	static const BlockType OBSIDIAN		("Obsidian",		true,  11,11,11,11,11,11);
	static const BlockType OAK_PLANKS	("Oak Planks",		true,  12,12,12,12,12,12);

	static const BlockType BLOCK_TYPES[] = {
		AIR,
		GRASS,
		DIRT,
		COBBLESTONE,
		STONE,
		BRICKS,
		BEDROCK,
		OAK_LOG,
		GOLD_BLOCK,
		DIORITE,
		OBSIDIAN,
		OAK_PLANKS
	};
}