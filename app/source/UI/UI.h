#pragma once

#pragma warning(push)
#pragma warning(disable:26495)
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#pragma warning(pop)
#include <unordered_map>
#include "BlockID.h"
#include "InventoryComponent.h"

class UI
{
public:
	enum class DragArray
	{
		INVENTORY,
		CRAFT,
		CRAFTING_RESULT,

		NONE
	};

	UI() = default;
	~UI() = default;

	bool Button(float posX, float posY, float sizeX, float sizeY, const char* image, const char* text);
	void Text(const ImVec2& position, ImFont* font, const char* texte);
	void Wallpaper(const float width, const float height, const char* path);

	/*Same Window TODO CHECK*/
	void Crosshair(const float width, const float height, const char* path, const float crossHairWidth, const float crossHairHeight);
	void DisplayLifePlayer(const float width, const float height, const char* path);
	void HotBar(const float width, const float height, const unsigned int* inventory);
	//-------------------------------------------------------------------------------------


	/*Same Window TODO CHECK*/
	void Inventory(const float width, const float height, InventoryComponent& inventory);
	void DragAndDropInventory(const float width, const float height, InventoryComponent& inventory, InventoryComponent& craft);
	void DragAndDropCrafting(const float width, const float height, InventoryComponent& inventory, InventoryComponent& craft);
	void DragAndDropCraftingResult(const float width, const float height, InventoryComponent& result);
	unsigned int m_countPush = 0;
	void InitFont();
	ImFont* m_normalFont = nullptr;
	ImFont* m_bigFont = nullptr;
private:
	DragArray m_currentDrag = DragArray::NONE;
	unsigned int* m_inventory = nullptr;
	ImVec2 m_fontSize{ 0.f,0.f };
	float m_cancelCursor = 3.f;
	float m_buttonSizeX = 0.f;
	float m_buttonSizeY = 0.f;
	ImVec4 m_colorButtonUnselected{ 0.f,0.f,0.f,0.f };
};