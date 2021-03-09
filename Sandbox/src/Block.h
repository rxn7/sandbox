#pragma once

#include "BlockType.h"
#include "BlocksContainer.cpp"

struct Block {
public:
	Block() {}
	Block(uint16_t type);
public:
	/// <summary> Set the m_type to the specified value. </summary>
	void setType(uint16_t type);
	
	/// <summary> Returns getType().solid(). </summary>
	inline bool solid() { return getType().solid(); }

	/// <summary> Returns BLOCK_TYPES[m_type] </summary>
	inline BlockType getType() { return Blocks::BLOCK_TYPES[m_type]; }
	
	/// <summary> Returns the m_type. </summary>
	inline uint16_t getTypeID() { return m_type; }
	
	/// <summary> Returns the tex coord of specified face. </summary>
	glm::vec2 getTextureCoord(uint8_t face);

private:
	uint16_t m_type = 0;
};