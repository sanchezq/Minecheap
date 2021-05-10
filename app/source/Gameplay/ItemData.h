#pragma once

#include "ItemID.h"

enum class ItemType
{
	NONE = 0,
	BLOCK,
	PICKAXE,
	SHOVEL,
	AXE,
	SWORD
};

struct ItemData
{
	ItemData() = default;
	ItemData(const ItemID id, const ItemType itemType, const int damage);
	ItemData(const ItemData& other) = default;
	ItemData& operator=(const ItemData& other) = delete;
	~ItemData() = default;

	ItemID m_ID = ItemID::ERROR;
	ItemType m_toolType = ItemType::NONE;
	int m_damage = 0;

};

