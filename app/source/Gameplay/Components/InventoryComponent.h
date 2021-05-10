#pragma once

#include "BlockID.h"
#include "ItemID.h"

class InventoryComponent
{
public:
	InventoryComponent() = default;
	InventoryComponent(const InventoryComponent& other) = delete;
	InventoryComponent& operator=(const InventoryComponent& other) = default;
	~InventoryComponent() = default;

	void AddOneItem(const ItemID id);

	int GetMaxStack() const;
	const unsigned int* GetObjectList() const;
	void SetSlot(const int slotNb, const int  id, const int quantity);
	void SwapSlot(const int slotA, const int slotB);
	void SetSize(const int size);


	unsigned int AddItems(const int index, const unsigned int numberOfBlocks);

	unsigned int GetSize()const;
	unsigned int GetItem(const int index) const;
	unsigned int GetItemQuantity(const int index) const;
	void RemoveItem(const int index);
	void ClearSlot(const int index);

private:
	unsigned int m_objectlist[120] = { 0 };
	unsigned int m_size = 9;
	unsigned int m_maxStack = 64;
};

