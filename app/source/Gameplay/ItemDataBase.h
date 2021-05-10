#pragma once

#include "ItemID.h"
#include "ItemData.h"
#include <unordered_map>

struct ItemDataBase
{
	ItemDataBase();
	ItemDataBase(const ItemDataBase& other) = delete;
	ItemDataBase& operator=(const ItemDataBase& other) = default;
	~ItemDataBase() = default;

	ItemData& GetData(const ItemID id);

	std::unordered_map <ItemID, ItemData> m_datas;
};