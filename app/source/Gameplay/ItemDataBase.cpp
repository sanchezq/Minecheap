#include "ItemDataBase.h"

ItemDataBase::ItemDataBase()
{
	m_datas.try_emplace(ItemID::ERROR, ItemData(ItemID::ERROR, ItemType::BLOCK, 0));

	m_datas.try_emplace(ItemID::AIR, ItemData(ItemID::AIR, ItemType::BLOCK, 0));
	m_datas.try_emplace(ItemID::GRASS, ItemData(ItemID::GRASS, ItemType::BLOCK, 0));
	m_datas.try_emplace(ItemID::DIRT, ItemData(ItemID::DIRT, ItemType::BLOCK, 0));
	m_datas.try_emplace(ItemID::GRAVEL, ItemData(ItemID::GRAVEL, ItemType::BLOCK, 0));
	m_datas.try_emplace(ItemID::WOOD, ItemData(ItemID::WOOD, ItemType::BLOCK, 0));
	m_datas.try_emplace(ItemID::LAVA, ItemData(ItemID::LAVA, ItemType::BLOCK, 0));
	m_datas.try_emplace(ItemID::WATER, ItemData(ItemID::WATER, ItemType::BLOCK, 0));
	m_datas.try_emplace(ItemID::LEAVES, ItemData(ItemID::STONE, ItemType::BLOCK, 0));
	m_datas.try_emplace(ItemID::STONE, ItemData(ItemID::STONE, ItemType::BLOCK, 0));


	m_datas.try_emplace(ItemID::SWORD, ItemData(ItemID::SWORD, ItemType::SWORD, 20));
	m_datas.try_emplace(ItemID::PICKAXE, ItemData(ItemID::PICKAXE, ItemType::PICKAXE, 2));
	m_datas.try_emplace(ItemID::SHOVEL, ItemData(ItemID::SHOVEL, ItemType::SHOVEL, 2));
	m_datas.try_emplace(ItemID::AXE, ItemData(ItemID::AXE, ItemType::AXE, 3));
}

ItemData& ItemDataBase::GetData(const ItemID id)
{
	std::unordered_map<ItemID, ItemData>::iterator it = m_datas.find(id);

	if (it == m_datas.end())
	{
		return  m_datas[ItemID::ERROR];
	}

	return m_datas[id];
}
