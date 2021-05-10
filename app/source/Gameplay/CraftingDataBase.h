#pragma once

#include "ItemID.h"
#include "InventoryComponent.h"
#include <unordered_map>

struct CraftRecipe
{
	CraftRecipe(const unsigned int item0, const unsigned int item1, const unsigned int item2, const unsigned int item3, const unsigned int item4, const unsigned int item5, const unsigned int item6, const unsigned int item7, const unsigned int item8);
	CraftRecipe(const CraftRecipe& other) = default;
	CraftRecipe& operator=(const CraftRecipe& other) = default;
	bool operator==(const CraftRecipe& other);
	~CraftRecipe();

	unsigned int m_item0;
	unsigned int m_item1;
	unsigned int m_item2;
	unsigned int m_item3;
	unsigned int m_item4;
	unsigned int m_item5;
	unsigned int m_item6;
	unsigned int m_item7;
	unsigned int m_item8;
};

struct CraftingDataBase
{
	CraftingDataBase();
	CraftingDataBase(const CraftingDataBase& other) = delete;
	CraftingDataBase& operator=(const CraftingDataBase& other) = default;
	~CraftingDataBase();

	ItemID GetData(const InventoryComponent& m_craftingList);

	std::vector <std::pair<CraftRecipe, ItemID>> m_datas;
};

