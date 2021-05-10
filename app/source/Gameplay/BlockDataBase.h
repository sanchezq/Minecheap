#pragma once

#include <unordered_map>
#include "BlockID.h"
#include "BlockData.h"

class BlockDataBase
{
public:
	BlockDataBase();
	BlockDataBase(const BlockDataBase& other) = delete;
	BlockDataBase& operator=(const BlockDataBase& other) = default;
	~BlockDataBase();

	BlockData& GetData(const BlockID id);

	std::unordered_map<BlockID, BlockData> m_datas;
};

