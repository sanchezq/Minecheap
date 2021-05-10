#include "CraftingDataBase.h"

CraftingDataBase::CraftingDataBase()
{

	//Add all recipies for crafting

	m_datas.push_back(std::pair<CraftRecipe, ItemID>({ (unsigned int)ItemID::WOOD, (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR,
														(unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR,
														(unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR },
														ItemID::WOOD_PLANK));

	m_datas.push_back(std::pair<CraftRecipe, ItemID>({ (unsigned int)ItemID::AIR, (unsigned int)ItemID::WOOD, (unsigned int)ItemID::AIR,
														(unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR,
														(unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR },
														ItemID::WOOD_PLANK));

	m_datas.push_back(std::pair<CraftRecipe, ItemID>({ (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR, (unsigned int)ItemID::WOOD,
														(unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR,
														(unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR },
														ItemID::WOOD_PLANK));

	m_datas.push_back(std::pair<CraftRecipe, ItemID>({ (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR,
														(unsigned int)ItemID::WOOD, (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR,
														(unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR },
														ItemID::WOOD_PLANK));

	m_datas.push_back(std::pair<CraftRecipe, ItemID>({ (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR,
														(unsigned int)ItemID::AIR, (unsigned int)ItemID::WOOD, (unsigned int)ItemID::AIR,
														(unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR },
														ItemID::WOOD_PLANK));

	m_datas.push_back(std::pair<CraftRecipe, ItemID>({ (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR,
														(unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR, (unsigned int)ItemID::WOOD,
														(unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR },
														ItemID::WOOD_PLANK));

	m_datas.push_back(std::pair<CraftRecipe, ItemID>({ (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR,
														(unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR,
														(unsigned int)ItemID::WOOD, (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR },
														ItemID::WOOD_PLANK));

	m_datas.push_back(std::pair<CraftRecipe, ItemID>({ (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR,
														(unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR,
														(unsigned int)ItemID::AIR, (unsigned int)ItemID::WOOD, (unsigned int)ItemID::AIR },
														ItemID::WOOD_PLANK));

	m_datas.push_back(std::pair<CraftRecipe, ItemID>({ (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR,
														(unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR,
														(unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR, (unsigned int)ItemID::WOOD },
														ItemID::WOOD_PLANK));



	m_datas.push_back(std::pair<CraftRecipe, ItemID>({ (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR,
														(unsigned int)ItemID::AIR, (unsigned int)ItemID::WOOD_PLANK, (unsigned int)ItemID::AIR,
														(unsigned int)ItemID::AIR, (unsigned int)ItemID::WOOD_PLANK, (unsigned int)ItemID::AIR },
														ItemID::STICK));

	m_datas.push_back(std::pair<CraftRecipe, ItemID>({ (unsigned int)ItemID::AIR, (unsigned int)ItemID::WOOD_PLANK, (unsigned int)ItemID::AIR,
														(unsigned int)ItemID::AIR, (unsigned int)ItemID::WOOD_PLANK, (unsigned int)ItemID::AIR,
														(unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR },
														ItemID::STICK));

	m_datas.push_back(std::pair<CraftRecipe, ItemID>({ (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR,
														(unsigned int)ItemID::WOOD_PLANK, (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR,
														(unsigned int)ItemID::WOOD_PLANK, (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR },
														ItemID::STICK));

	m_datas.push_back(std::pair<CraftRecipe, ItemID>({ (unsigned int)ItemID::WOOD_PLANK, (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR,
														(unsigned int)ItemID::WOOD_PLANK, (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR,
														(unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR },
														ItemID::STICK));

	m_datas.push_back(std::pair<CraftRecipe, ItemID>({ (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR,
														(unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR, (unsigned int)ItemID::WOOD_PLANK,
														(unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR, (unsigned int)ItemID::WOOD_PLANK },
														ItemID::STICK));

	m_datas.push_back(std::pair<CraftRecipe, ItemID>({ (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR, (unsigned int)ItemID::WOOD_PLANK,
														(unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR, (unsigned int)ItemID::WOOD_PLANK,
														(unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR },
														ItemID::STICK));



	m_datas.push_back(std::pair<CraftRecipe, ItemID>({ (unsigned int)ItemID::AIR, (unsigned int)ItemID::STONE, (unsigned int)ItemID::AIR,
														(unsigned int)ItemID::AIR, (unsigned int)ItemID::STONE, (unsigned int)ItemID::AIR,
														(unsigned int)ItemID::AIR, (unsigned int)ItemID::STICK, (unsigned int)ItemID::AIR },
														ItemID::SWORD));

	m_datas.push_back(std::pair<CraftRecipe, ItemID>({ (unsigned int)ItemID::STONE, (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR,
													   (unsigned int)ItemID::STONE, (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR,
													   (unsigned int)ItemID::STICK, (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR },
													   ItemID::SWORD));

	m_datas.push_back(std::pair<CraftRecipe, ItemID>({ (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR, (unsigned int)ItemID::STONE,
													   (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR, (unsigned int)ItemID::STONE,
													   (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR, (unsigned int)ItemID::STICK },
													   ItemID::SWORD));

	m_datas.push_back(std::pair<CraftRecipe, ItemID>({ (unsigned int)ItemID::STONE, (unsigned int)ItemID::STONE, (unsigned int)ItemID::STONE,
													   (unsigned int)ItemID::AIR, (unsigned int)ItemID::STICK, (unsigned int)ItemID::AIR,
													   (unsigned int)ItemID::AIR, (unsigned int)ItemID::STICK, (unsigned int)ItemID::AIR },
													   ItemID::PICKAXE));

	m_datas.push_back(std::pair<CraftRecipe, ItemID>({ (unsigned int)ItemID::AIR, (unsigned int)ItemID::STONE, (unsigned int)ItemID::AIR,
													   (unsigned int)ItemID::AIR, (unsigned int)ItemID::STICK, (unsigned int)ItemID::AIR,
													   (unsigned int)ItemID::AIR, (unsigned int)ItemID::STICK, (unsigned int)ItemID::AIR },
													   ItemID::SHOVEL));

	m_datas.push_back(std::pair<CraftRecipe, ItemID>({ (unsigned int)ItemID::STONE, (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR,
													   (unsigned int)ItemID::STICK, (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR,
													   (unsigned int)ItemID::STICK, (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR },
													   ItemID::SHOVEL));

	m_datas.push_back(std::pair<CraftRecipe, ItemID>({ (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR, (unsigned int)ItemID::STONE,
													   (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR, (unsigned int)ItemID::STICK,
													   (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR, (unsigned int)ItemID::STICK },
													   ItemID::SHOVEL));


	m_datas.push_back(std::pair<CraftRecipe, ItemID>({ (unsigned int)ItemID::STONE, (unsigned int)ItemID::STONE, (unsigned int)ItemID::AIR,
													   (unsigned int)ItemID::STONE, (unsigned int)ItemID::STICK, (unsigned int)ItemID::AIR,
													   (unsigned int)ItemID::AIR, (unsigned int)ItemID::STICK, (unsigned int)ItemID::AIR },
													   ItemID::AXE));

	m_datas.push_back(std::pair<CraftRecipe, ItemID>({ (unsigned int)ItemID::AIR, (unsigned int)ItemID::STONE, (unsigned int)ItemID::STONE,
													   (unsigned int)ItemID::AIR, (unsigned int)ItemID::STICK, (unsigned int)ItemID::STONE,
													   (unsigned int)ItemID::AIR, (unsigned int)ItemID::STICK, (unsigned int)ItemID::AIR },
													   ItemID::AXE));



	m_datas.push_back(std::pair<CraftRecipe, ItemID>({ (unsigned int)ItemID::WOOD_PLANK, (unsigned int)ItemID::WOOD_PLANK, (unsigned int)ItemID::WOOD_PLANK,
														(unsigned int)ItemID::WOOD_PLANK, (unsigned int)ItemID::AIR, (unsigned int)ItemID::WOOD_PLANK,
														(unsigned int)ItemID::WOOD_PLANK, (unsigned int)ItemID::WOOD_PLANK, (unsigned int)ItemID::WOOD_PLANK },
														ItemID::CHEST));



	m_datas.push_back(std::pair<CraftRecipe, ItemID>({ (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR,
														(unsigned int)ItemID::AIR, (unsigned int)ItemID::WOOD, (unsigned int)ItemID::AIR,
														(unsigned int)ItemID::AIR, (unsigned int)ItemID::STICK, (unsigned int)ItemID::AIR },
														ItemID::TORCH));

	m_datas.push_back(std::pair<CraftRecipe, ItemID>({ (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR, (unsigned int)ItemID::WOOD,
														(unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR, (unsigned int)ItemID::STICK,
														(unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR },
														ItemID::TORCH));

	m_datas.push_back(std::pair<CraftRecipe, ItemID>({ (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR,
														(unsigned int)ItemID::WOOD, (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR,
														(unsigned int)ItemID::STICK, (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR },
														ItemID::TORCH));

	m_datas.push_back(std::pair<CraftRecipe, ItemID>({ (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR,
														(unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR, (unsigned int)ItemID::WOOD,
														(unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR, (unsigned int)ItemID::STICK },
														ItemID::TORCH));

	m_datas.push_back(std::pair<CraftRecipe, ItemID>({ (unsigned int)ItemID::WOOD, (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR,
														(unsigned int)ItemID::STICK, (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR,
														(unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR },
														ItemID::TORCH));

	m_datas.push_back(std::pair<CraftRecipe, ItemID>({ (unsigned int)ItemID::AIR, (unsigned int)ItemID::WOOD, (unsigned int)ItemID::AIR,
														(unsigned int)ItemID::AIR, (unsigned int)ItemID::STICK, (unsigned int)ItemID::AIR,
														(unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR },
														ItemID::TORCH));


	m_datas.push_back(std::pair<CraftRecipe, ItemID>({ (unsigned int)ItemID::AIR, (unsigned int)ItemID::GRAVEL, (unsigned int)ItemID::AIR,
														(unsigned int)ItemID::AIR, (unsigned int)ItemID::STICK, (unsigned int)ItemID::AIR,
														(unsigned int)ItemID::AIR, (unsigned int)ItemID::STONE, (unsigned int)ItemID::AIR },
														ItemID::ARROW));

	m_datas.push_back(std::pair<CraftRecipe, ItemID>({ (unsigned int)ItemID::GRAVEL, (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR,
														(unsigned int)ItemID::STICK, (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR,
														(unsigned int)ItemID::STONE, (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR },
														ItemID::ARROW));

	m_datas.push_back(std::pair<CraftRecipe, ItemID>({ (unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR, (unsigned int)ItemID::GRAVEL,
														(unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR, (unsigned int)ItemID::STICK,
														(unsigned int)ItemID::AIR, (unsigned int)ItemID::AIR, (unsigned int)ItemID::STONE },
														ItemID::ARROW));

	m_datas.push_back(std::pair<CraftRecipe, ItemID>({ (unsigned int)ItemID::STICK, (unsigned int)ItemID::STICK, (unsigned int)ItemID::AIR,
														(unsigned int)ItemID::STICK, (unsigned int)ItemID::AIR, (unsigned int)ItemID::STICK,
														(unsigned int)ItemID::STICK, (unsigned int)ItemID::STICK, (unsigned int)ItemID::AIR },
														ItemID::BOW));

	m_datas.push_back(std::pair<CraftRecipe, ItemID>({ (unsigned int)ItemID::AIR, (unsigned int)ItemID::STICK, (unsigned int)ItemID::STICK,
													(unsigned int)ItemID::STICK, (unsigned int)ItemID::AIR, (unsigned int)ItemID::STICK,
													(unsigned int)ItemID::AIR, (unsigned int)ItemID::STICK, (unsigned int)ItemID::STICK },
													ItemID::BOW));
}

CraftingDataBase::~CraftingDataBase()
{
}

ItemID CraftingDataBase::GetData(const InventoryComponent& m_craftingList)
{
	CraftRecipe id{ m_craftingList.GetItem(0), m_craftingList.GetItem(1), m_craftingList.GetItem(2),
				    m_craftingList.GetItem(3), m_craftingList.GetItem(4), m_craftingList.GetItem(5),
					m_craftingList.GetItem(6), m_craftingList.GetItem(7), m_craftingList.GetItem(8) };


	for (int index = 0; index < m_datas.size(); index++)
	{
		if (m_datas[index].first == id)
		{
			return m_datas[index].second;
		}
	}

	return ItemID::AIR;
}

CraftRecipe::CraftRecipe(const unsigned int item0, const unsigned int item1, const unsigned int item2, const unsigned int item3, const unsigned int item4, const unsigned int item5, const unsigned int item6, const unsigned int item7, const unsigned int item8) :
	m_item0(item0), m_item1(item1), m_item2(item2), m_item3(item3), m_item4(item4), m_item5(item5), m_item6(item6), m_item7(item7), m_item8(item8)
{
}


bool CraftRecipe::operator==(const CraftRecipe& other)
{
	if (m_item0 == other.m_item0 && m_item1 == other.m_item1 && m_item2 == other.m_item2 &&
		m_item3 == other.m_item3 && m_item4 == other.m_item4 && m_item5 == other.m_item5 &&
		m_item6 == other.m_item6 && m_item7 == other.m_item7 && m_item8 == other.m_item8)
	{
		return true;
	}

	return false;
}

CraftRecipe::~CraftRecipe()
{
}
