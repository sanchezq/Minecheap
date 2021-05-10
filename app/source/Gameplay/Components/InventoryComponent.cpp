#include "InventoryComponent.h"

void InventoryComponent::SetSize(const int size)
{
	m_size = size;
}

void InventoryComponent::AddOneItem(const ItemID id)
{
	if (id == ItemID::ERROR)
	{
		return;
	}

	// Check if  you already have this kind of block on  your inventory
	for (unsigned int index = 0; index < m_size * 2; index += 2)
	{
		if (m_objectlist[index] == (unsigned int)id && m_objectlist[index + 1] < m_maxStack)
		{
			m_objectlist[index + 1] += 1;
			return;
		}
	}

	// If you dont, find the first empty slot
	for (unsigned int index = 0; index < m_size * 2; index += 2)
	{
		if (m_objectlist[index] == 0)
		{
			m_objectlist[index] = (unsigned int)id;
			m_objectlist[index + 1] = 1;
			return;
		}
	}
}


int InventoryComponent::GetMaxStack() const
{
	return m_maxStack;
}

const unsigned int* InventoryComponent::GetObjectList() const
{
	return m_objectlist;
}

void InventoryComponent::SetSlot(const int slotNb, const int id, const int quantity)
{
	m_objectlist[0 + slotNb * 2] = id;
	m_objectlist[1 + slotNb * 2] = quantity;
}

void InventoryComponent::SwapSlot(const int blockA, const int blockB)
{
	unsigned int tempIDA = m_objectlist[blockA *2];
	unsigned int tempQtyA = m_objectlist[2*blockA +1];

	m_objectlist[2*blockA] = m_objectlist[2*blockB];
	m_objectlist[2*blockA + 1] = m_objectlist[2*blockB + 1];

	m_objectlist[2*blockB] = tempIDA;
	m_objectlist[2*blockB + 1] = tempQtyA;
}

unsigned int InventoryComponent::AddItems(const int index, const unsigned int numberOfBlocks)
{
	m_objectlist[index * 2 + 1] += numberOfBlocks;

	if (m_objectlist[index * 2 + 1] > m_maxStack)
	{
		int rest = m_objectlist[index * 2 + 1] - m_maxStack;
		m_objectlist[index * 2 + 1] = m_maxStack;
		return rest;
	}

	return 0;
}

unsigned int InventoryComponent::GetSize() const
{
	return m_size;
}

unsigned int InventoryComponent::GetItem(const int index) const
{
	return m_objectlist[index * 2];
}

unsigned int InventoryComponent::GetItemQuantity(const int index) const
{
	return m_objectlist[index * 2 + 1];
}

void InventoryComponent::RemoveItem(const int index)
{
	if (m_objectlist[index * 2 + 1] > 0)
	{
		m_objectlist[index * 2 + 1] -= 1;
	}

	if (m_objectlist[index * 2 + 1] == 0)
	{
		ClearSlot(index);
	}
}

void InventoryComponent::ClearSlot(const int index)
{
	m_objectlist[0 + index * 2] = 0;
	m_objectlist[1 + index * 2] = 0;
}
