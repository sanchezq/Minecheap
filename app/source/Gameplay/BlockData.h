#pragma once

#include<unordered_map>
#include "BlockID.h"

enum class BlockClassType
{
	SOLID = 0,
	LIQUID,
	INTERRACTABLE
};

enum class BlockDestructType
{
	 NONE = 0,
	 UNBREAKABLE,
	 PICKAXE,
	 SHOVEL,
	 AXE,
	 SWORD
};

struct BlockData
{
	BlockData() = default;
	BlockData(const BlockID id, const BlockClassType classType, const BlockDestructType destructType, const float durability, const bool isGravity, const float fluidity, const unsigned int distance, const float updateTime);
	BlockData(const BlockData& other) = default;
	BlockData& operator=(const BlockData& other) = delete;
	~BlockData() = default;

	BlockID m_ID = BlockID::AIR;
	BlockClassType m_classType = BlockClassType::SOLID;
	BlockDestructType m_destructType = BlockDestructType::NONE;
	float m_durability = 0.0f;
	bool m_isGravity = false;
	float m_fluidity = 0.0f;
	unsigned int m_distance = 0;
	float m_updateTime = .5f;
};

