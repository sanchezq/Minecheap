#include "ItemData.h"

ItemData::ItemData(const ItemID id, const ItemType itemType, const int damage) :
	m_ID(id), m_toolType(itemType), m_damage(damage)
{
}
