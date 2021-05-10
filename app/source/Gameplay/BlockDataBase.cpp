#include "BlockDataBase.h"

BlockDataBase::BlockDataBase()
{
	m_datas.try_emplace(BlockID::ERROR, BlockData(BlockID::ERROR, BlockClassType::SOLID, BlockDestructType::NONE, 0, false, 0, 0, 0));

	m_datas.try_emplace(BlockID::AIR, BlockData(BlockID::AIR, BlockClassType::SOLID, BlockDestructType::NONE, 0, false, 0, 0, 0));

	m_datas.try_emplace(BlockID::GRASS, BlockData(BlockID::GRASS, BlockClassType::SOLID, BlockDestructType::SHOVEL, 10, false, 0, 0, 0));
	m_datas.try_emplace(BlockID::DIRT, BlockData(BlockID::DIRT, BlockClassType::SOLID, BlockDestructType::SHOVEL, 10, false, 0, 0, 0));
	m_datas.try_emplace(BlockID::GRAVEL, BlockData(BlockID::GRAVEL, BlockClassType::SOLID, BlockDestructType::SHOVEL, 10, true, 0, 0, 0.2f));
	m_datas.try_emplace(BlockID::WOOD, BlockData(BlockID::WOOD, BlockClassType::SOLID, BlockDestructType::AXE, 10, false, 0, 0, 0));

	m_datas.try_emplace(BlockID::LAVA, BlockData(BlockID::LAVA, BlockClassType::LIQUID, BlockDestructType::NONE, 0, false, 2, 3, 1.f));
	m_datas.try_emplace(BlockID::WATER, BlockData(BlockID::WATER, BlockClassType::LIQUID, BlockDestructType::NONE, 0, false, 1, 7, 0.2f));

	m_datas.try_emplace(BlockID::LEAVES, BlockData(BlockID::LEAVES, BlockClassType::SOLID, BlockDestructType::NONE, 10, false, 0, 0, 0));
	m_datas.try_emplace(BlockID::STONE, BlockData(BlockID::STONE, BlockClassType::SOLID, BlockDestructType::PICKAXE, 10, false, 0, 0, 0));
	m_datas.try_emplace(BlockID::WOOD_PLANK, BlockData(BlockID::WOOD_PLANK, BlockClassType::SOLID, BlockDestructType::AXE, 10, false, 0, 0, 0));

	m_datas.try_emplace(BlockID::CHEST, BlockData(BlockID::CHEST, BlockClassType::INTERRACTABLE, BlockDestructType::AXE, 10, false, 0, 0, 0));
	m_datas.try_emplace(BlockID::TORCH, BlockData(BlockID::TORCH, BlockClassType::SOLID, BlockDestructType::NONE, 1, false, 0, 0, 0));
}

BlockDataBase::~BlockDataBase()
{
	m_datas.clear();
}

BlockData& BlockDataBase::GetData(const BlockID id)
{
	std::unordered_map<BlockID, BlockData>::iterator it = m_datas.find(id);

	if (it == m_datas.end())
	{
		return m_datas[BlockID::ERROR];
	}

	return m_datas[id];
}
