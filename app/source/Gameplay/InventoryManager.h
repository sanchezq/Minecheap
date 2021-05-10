#pragma once
#include "InventoryComponent.h"
#include "CraftingDataBase.h"
#include "ItemID.h"

class InventoryManager
{
public:
	InventoryManager() = default;
	InventoryManager(const InventoryManager& other) = delete;
	InventoryManager& operator=(const InventoryManager& other) = default;//TODO felix
	~InventoryManager() = default;

	InventoryComponent& MutateCraft();
	InventoryComponent& MutateCraftingResult();
	void CraftInteractions(InventoryComponent& craft, const unsigned int destIndex, const unsigned int index);
	void InventoryInteractions(InventoryComponent& inventory, const unsigned int destIndex, const unsigned int index);
	void InteractionInventoryToCraft(InventoryComponent& inventory, const unsigned int indexInventory, InventoryComponent& craft, const unsigned int indexCraft);
	void InteractionCraftToInventory(InventoryComponent& inventory, const unsigned int indexInventory, InventoryComponent& craft, const unsigned int indexCraft);
	void CraftingResultInteractions(InventoryComponent& inventory, const unsigned int indexInventory, InventoryComponent& craftingResult, const unsigned int index);
	void ClearCraft(InventoryComponent& inventory);


	const CraftingDataBase& GetCraftingDataBase() const;
	CraftingDataBase& MutateCraftingDataBase();

private:
	//TODO create Define Size craft
	InventoryComponent m_craft;
	InventoryComponent m_craftingResult;

	CraftingDataBase m_craftingDataBase;

};

