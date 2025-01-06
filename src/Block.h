#pragma once

#include "BlockType.h"
#include "BlocksContainer.h"

struct Block {
public:
	Block() {}
	Block(uint16_t type);
public:
	/// <summary> Set the m_type to the specified value. </summary>
	void SetType(uint16_t type);
	
	/// <summary> Returns getType().solid(). </summary>
	bool IsSolid() const;

	/// <summary> Returns BLOCK_TYPES[m_type] </summary>
	BlockType* GetType() const;
	
	/// <summary> Returns the m_type. </summary>
	uint16_t GetTypeID() const;
	
	/// <summary> Returns the tex coord of specified face. </summary>
	uint16_t GetTextureID(uint8_t face) const;

private:
	uint16_t m_type = 0;
};