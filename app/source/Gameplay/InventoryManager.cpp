#include "InventoryManager.h"
#include "BlockID.h"

InventoryComponent& InventoryManager::MutateCraft()
{
	return m_craft;
}

InventoryComponent& InventoryManager::MutateCraftingResult()
{
	return m_craftingResult;
}

void InventoryManager::CraftInteractions(InventoryComponent& craft, const unsigned int destIndex, const unsigned int index)
{
	//TODO modify this
	unsigned int blockID = craft.GetItem(index);
	unsigned int blockQty = craft.GetItemQuantity(index);

	unsigned int destblockID = craft.GetItem(destIndex);
	unsigned int destblockQty = craft.GetItemQuantity(destIndex);
	unsigned int maxStack = craft.GetMaxStack();

	if (blockID == destblockID)
	{
		if (destblockQty < maxStack)
		{
			int restblocks = craft.AddItems(destIndex, blockQty);
			if (0 < restblocks)
			{
				craft.SetSlot(index, blockID, restblocks);
			}
			else
			{
				craft.ClearSlot(index);
			}
		}
	}
	else
	{
		craft.SwapSlot(index, destIndex);
	}

	int ItemData = (int)m_craftingDataBase.GetData(craft);
	if (ItemData == 0)
	{
		m_craftingResult.ClearSlot(0);
	}
	else
	{
		m_craftingResult.SetSlot(0, ItemData, 1);
	}
}

void InventoryManager::InventoryInteractions(InventoryComponent& inventory, const unsigned int destIndex, const unsigned int index)
{
	unsigned int blockID = inventory.GetItem(index);
	unsigned int blockQty = inventory.GetItemQuantity(index);

	unsigned int destblockID = inventory.GetItem(destIndex);
	unsigned int destblockQty = inventory.GetItemQuantity(destIndex);

	unsigned int maxStack = inventory.GetMaxStack();

	if (blockID != (unsigned int)BlockID::AIR)
	{
		if (blockID == destblockID)
		{
			if (destblockQty < maxStack)
			{
				int restblocks = inventory.AddItems(destIndex, blockQty);
				if (0 < restblocks)
				{
					inventory.SetSlot(index, blockID, restblocks);
				}
				else
				{
					inventory.ClearSlot(index);
				}
			}
		}
		else
		{
			inventory.SwapSlot(index, destIndex);
		}
	}
}

void InventoryManager::InteractionInventoryToCraft(InventoryComponent& inventory, const unsigned int indexInventory, InventoryComponent& craft, const unsigned int indexCraft)
{
	unsigned int blockQty = craft.GetItemQuantity(indexCraft);
	unsigned int maxStack = craft.GetMaxStack();
	unsigned int craftID = craft.GetItem(indexCraft);
	unsigned int inventID = inventory.GetItem(indexInventory);

	if (inventID != (unsigned int)BlockID::AIR)
	{
		if (craftID == (unsigned int)BlockID::AIR)
		{
			craft.SetSlot(indexCraft, inventID, blockQty + 1);
			inventory.RemoveItem(indexInventory);
		}
		else if (craftID == inventID)
		{
			if (blockQty < maxStack)
			{
				craft.SetSlot(indexCraft, inventID, blockQty + 1);
				inventory.RemoveItem(indexInventory);
			}
		}
	}

	int ItemData = (int)m_craftingDataBase.GetData(craft);
	if (ItemData == 0)
	{
		m_craftingResult.ClearSlot(0);
	}
	else
	{
		m_craftingResult.SetSlot(0, ItemData, 1);
	}

}

void InventoryManager::InteractionCraftToInventory(InventoryComponent& inventory, const unsigned int indexInventory, InventoryComponent& craft, const unsigned int indexCraft)
{
	unsigned int inventID = inventory.GetItem(indexInventory);
	unsigned int craftID = craft.GetItem(indexCraft);
	unsigned int blockQty = inventory.GetItemQuantity(indexInventory);
	unsigned int maxStack = inventory.GetMaxStack();
	if (craftID != (unsigned int)BlockID::AIR)
	{
		if (inventID == static_cast<int>(BlockID::AIR))
		{
			inventory.SetSlot(indexInventory, craftID, blockQty + 1);
			craft.RemoveItem(indexCraft);
		}
		else if (craftID == inventID)
		{
			if (blockQty < maxStack)
			{
				inventory.SetSlot(indexInventory, craftID, blockQty + 1);
				craft.RemoveItem(indexCraft);
			}
		}
	}
	
	int ItemData = (int)m_craftingDataBase.GetData(craft);
	if (ItemData == 0)
	{
		m_craftingResult.ClearSlot(0);
	}
	else
	{
		m_craftingResult.SetSlot(0, ItemData, 1);
	}
}

void InventoryManager::CraftingResultInteractions(InventoryComponent& inventory, const unsigned int indexInventory, InventoryComponent& craftingResult, const unsigned int index)
{
	unsigned int craftingID = craftingResult.GetItem(index);
	unsigned int qty = craftingResult.GetItemQuantity(index);
	unsigned int inventID = inventory.GetItem(indexInventory);
	if (inventID == static_cast<int>(BlockID::AIR))
	{
		inventory.SetSlot(indexInventory,craftingID,qty);
		craftingResult.RemoveItem(index);
		for (unsigned int i = 0; i <= m_craft.GetSize(); i++)
		{
			m_craft.ClearSlot(i);
		}
	}
}

void InventoryManager::ClearCraft(InventoryComponent& inventory)
{
	/*Clear*/
	//pass all objects in inventary
	for (unsigned int index = 0; index <= m_craft.GetSize(); index++)
	{
		unsigned int itemID = m_craft.GetItem(index);
		if (itemID != static_cast<int>(BlockID::AIR))
		{
			for (unsigned int i = 0; i <= inventory.GetSize(); i++)
			{
				if (itemID == inventory.GetItem(i))
				{
					int restblocks = inventory.AddItems(i, m_craft.GetItemQuantity(index));
					if (0 < restblocks)
					{
						for (unsigned int indexAir = 0; indexAir <= inventory.GetSize(); indexAir++)
						{
							if (static_cast<int>(BlockID::AIR) == inventory.GetItem(indexAir))
							{
								inventory.SetSlot(indexAir,itemID, restblocks);
								m_craft.ClearSlot(index);
								break;
							}
						}
					}
					else
					{
						m_craft.ClearSlot(index);
					}
				}
			}
		}
	}
	m_craftingResult.ClearSlot(0);
}

const CraftingDataBase& InventoryManager::GetCraftingDataBase() const
{
	return m_craftingDataBase;
}

CraftingDataBase& InventoryManager::MutateCraftingDataBase()
{
	return m_craftingDataBase;
}
