#include "UI.h"
#include "Resources/TextureManager.h"
#include "Resources/ResourcesManager.h"
#include "App.h"
#include "ResourceGFX.h"
#include "GameManager.h"
#include <string>

//ImGui::ShowDemoWindow();-->reserche resource
bool UI::Button(float posX, float posY, float sizeX, float sizeY, const char* image, const char* text)
{
	GLuint id = Resources::ResourcesManager::GetTexture(image, false);
	ImGui::SetCursorPos(ImVec2(posX, posY));
	ImGui::PushStyleColor(ImGuiCol_Button, m_colorButtonUnselected);
	m_countPush++;
	if (ImGui::ImageButton((void*)(intptr_t)id, ImVec2(sizeX, sizeY)))
	{
		return true;
	}
	m_fontSize = ImGui::CalcTextSize(text);
	ImGui::SetCursorPos(ImVec2(posX + (sizeX * 0.5f) - (m_fontSize.x * 0.5f) + m_cancelCursor, posY + (sizeY * 0.5f) - (m_fontSize.y * 0.5f) + m_cancelCursor));
	ImGui::PushFont(m_normalFont);
	ImGui::Text(text);
	ImGui::PopFont();
	return false;
}

void UI::Text(const ImVec2& position, ImFont* font, const char* texte)
{
	ImGui::SetCursorPos(position);
	ImGui::PushFont(font);
	ImGui::Text(texte);
	ImGui::PopFont();
}

void UI::Crosshair(const float width, const float height, const char* path, const float crossHairWidth, const float crossHairHeight)
{	
	GLuint my_image_texture = Resources::ResourcesManager::GetTexture(path, false);
	ImGui::SetCursorPos(ImVec2(width * 0.5f, height * 0.5f));//0.5-> midle of window
	ImGui::Image((void*)(intptr_t)my_image_texture, ImVec2(width * crossHairWidth, height * crossHairHeight));
}

void UI::DisplayLifePlayer(const float width, const float height, const char* path)
{
	GLuint id = Resources::ResourcesManager::GetTexture(path, false);
	float life = App::GetGameManager().MutateWorld().m_player.GetHealth();
	//TODO define max life
	float maxLife = 100.f;
	float cursor = 9;
	float healthRange = 0;
	//TODO verify the logic ----->I'm tired
	for (float i = 10.f; i < maxLife + 10.f; i+=10.f)
	{
		ImGui::SetCursorPos(ImVec2(width * 0.3f + (width * 0.02f * cursor) , height * 0.84f));
		if (life >= (maxLife - 0.5 - healthRange))
		{
			ImGui::Image((void*)(intptr_t)id, ImVec2(width * 0.016f, height * 0.04f), { 0.f,0.f }, { 1.f / 3.f ,1.f });
		}
		else if(life <= (maxLife - 0.5 - healthRange) && life > (maxLife - i) )
		{
			ImGui::Image((void*)(intptr_t)id, ImVec2(width * 0.016f, height * 0.04f), { 1.f / 3.f,0.f }, { 1.f / 1.5f ,1.f });
		}
		else
		{
			ImGui::Image((void*)(intptr_t)id, ImVec2(width * 0.016f, height * 0.04f), { 1.f / 1.5f,0.f }, { 1.f ,1.f });
		}
		cursor--;
		healthRange += 10;
	}
}

void UI::HotBar(const float width, const float height, const unsigned int* inventory)
{ 
	GLuint id = Resources::ResourcesManager::GetTexture("resources/Images/Game/hotBar.png", false);
	ImGui::SetCursorPos(ImVec2(width * 0.3f, height * 0.891f));
	ImGui::Image((void*)(intptr_t)id, ImVec2(width * 0.46f, height * 0.08f));


	id = Resources::ResourcesManager::GetTexture("resources/Images/Blocks/blocks.png", false);
	std::string numberOfBlock;
	int number = inventory[1];
	for (size_t i = 0; i < 18; i += 2)
	{
		number = inventory[i + 1]; 
		numberOfBlock = std::to_string(number);
		ImGui::SetCursorPos(ImVec2(width * 0.308f + (width* 0.0252f) * i, height * 0.905f));


		/*Calcul Texel*/
		float itemTexture = (float)inventory[i];
		int y = (int)(itemTexture * 0.1f);
		int x = (int)itemTexture % 10;
		ImGui::Image((void*)(intptr_t)id, ImVec2(width * 0.04f, height * 0.055f), { 0.1f * x, 0.f + 0.1f * y }, { 0.1f * x + 0.1f, 0.1f + 0.1f * y });

		ImGui::SetCursorPos(ImVec2(width * 0.332f + (width * 0.0256f) * i, height * 0.944f));
		ImGui::Text(numberOfBlock.c_str());
	}

	id = Resources::ResourcesManager::GetTexture("resources/Images/Game/selection.png", false);
	ImGui::SetCursorPos(ImVec2(width * 0.3f + (width * 0.0504f) * App::GetGameManager().MutateWorld().m_player.GetSelectedIndex(), height * 0.889f));
	ImGui::Image((void*)(intptr_t)id, ImVec2(width * 0.056f, height * 0.0875f));
}

void UI::Wallpaper(const float width, const float height, const char* path)
{
	bool wallpaper = true;
	ImGui::SetNextWindowPos(ImVec2(-5, -2));
	ImGui::SetNextWindowSize({ width + 20, height + 20 });
	ImGui::SetNextWindowBgAlpha(0.002f);//---------------->Set alpha window
	ImGui::Begin("wallpaper", &wallpaper, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
	GLuint id = Resources::ResourcesManager::GetTexture(path, false);
	ImGui::SetCursorPos(ImVec2(width * 0.3f, height * 0.2f));
	ImGui::Image((void*)(intptr_t)id, ImVec2(width * 0.44f, height * 0.6875f));
	ImGui::End();
}

void UI::Inventory(const float width, const float height, InventoryComponent& inventory)
{
	Wallpaper(width, height,"resources/Images/Game/inventory.png" );
	DragAndDropInventory(width, height, inventory, App::GetGameManager().MutateInventoryManager().MutateCraft());
	DragAndDropCraftingResult(width, height, App::GetGameManager().MutateInventoryManager().MutateCraftingResult());
	DragAndDropCrafting(width, height, inventory, App::GetGameManager().MutateInventoryManager().MutateCraft());

	ImGui::End();
}

void UI::DragAndDropInventory(const float width, const float height, InventoryComponent& inventory, InventoryComponent& craft)
{
	bool test = true;
	ImGui::SetNextWindowPos(ImVec2(-5, -2));
	ImGui::SetNextWindowSize({ width + 20, height + 20 });
	ImGui::Begin("Settings", &test, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground);

	GLuint id = Resources::ResourcesManager::GetTexture("resources/Images/Blocks/blocks.png", false);
	int spacingY = 0;
	int spacingX = 0;

	for (int i = inventory.GetSize() - 1; i > -1; i--)
	{
		ImGui::PushID(i);
		if (spacingX == 0)
		{
			spacingX = 8;//hieghtStart ------------  Espacement Height
			ImGui::SetCursorPosY((height * 0.553f) + (height * 0.075f * spacingY));
			spacingY++;
		}
		else
		{
			spacingX--;
			ImGui::SameLine();
		}

		if (spacingY == 4)
		{
			ImGui::SetCursorPosY((height * 0.553f) + (height * 0.24f));
			spacingY = 0;
		}

		ImGui::SetCursorPos(ImVec2(width * 0.309f + spacingX * (width * 0.048f), ImGui::GetCursorPosY()));
		ImVec2 cursor = ImGui::GetCursorPos();

		/*Calcul Texel*/
		float itemTexture = (float)inventory.GetItem(i);
		int y = (int)(itemTexture * 0.1f);
		int x = (int)itemTexture % 10;
		ImGui::ImageButton((void*)(intptr_t)id, ImVec2(width * 0.0336f, height * 0.0525f), { 0.1f * x, 0.f + 0.1f * y }, { 0.1f * x + 0.1f, 0.1f + 0.1f * y });


		ImGuiDragDropFlags src_flags = 0;
		src_flags |= ImGuiDragDropFlags_SourceNoDisableHover;     // Keep the source displayed as hovered
		src_flags |= ImGuiDragDropFlags_SourceNoHoldToOpenOthers; // Because our dragging is local, we disable the feature of opening foreign treenodes/tabs while dragging
		if (ImGui::BeginDragDropSource(src_flags))
		{
			m_currentDrag = DragArray::INVENTORY;
			ImGui::SetDragDropPayload("DragAndDropArray", &i, sizeof(unsigned int));


			ImGui::ImageButton((void*)(intptr_t)id, ImVec2(width * 0.0336f, height * 0.0525f), { 0.1f * x, 0.f + 0.1f * y }, { 0.1f * x + 0.1f, 0.1f + 0.1f * y });
			ImGui::EndDragDropSource();
		}
		if (ImGui::BeginDragDropTarget())
		{
			ImGuiDragDropFlags target_flags = 0;
			target_flags |= ImGuiDragDropFlags_AcceptBeforeDelivery;    // Don't wait until the delivery (release mouse button on a target) to do something
			target_flags |= ImGuiDragDropFlags_AcceptNoDrawDefaultRect; // Don't display the yellow rectangle
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DragAndDropArray", target_flags))
			{
				IM_ASSERT(payload->DataSize == sizeof(unsigned int));
				unsigned int payload_n = *(const unsigned int*)payload->Data;

				if (ImGui::IsMouseReleased(ImGuiMouseButton_Left))
				{
					/*Add logic System*/
					if (m_currentDrag == DragArray::INVENTORY)
					{
						App::GetGameManager().MutateInventoryManager().InventoryInteractions(inventory, i, payload_n);
					}
					if (m_currentDrag == DragArray::CRAFT)
					{
						App::GetGameManager().MutateInventoryManager().InteractionCraftToInventory(inventory, i, craft, payload_n);
					}
					if (m_currentDrag == DragArray::CRAFTING_RESULT)
					{
						App::GetGameManager().MutateInventoryManager().CraftingResultInteractions(inventory, i, App::GetGameManager().MutateInventoryManager().MutateCraftingResult(), payload_n);
					}
				}
			}
			ImGui::EndDragDropTarget();
		}
		ImGui::PopID();

		std::string text = std::to_string(inventory.GetItemQuantity(i));
		ImGui::SetCursorPos(cursor);
		ImGui::Text(text.c_str());
	}
}

void UI::DragAndDropCrafting(const float width, const float height, InventoryComponent& inventory, InventoryComponent& craft)
{
	int spacingY = 0;
	int spacingX = 0;

	GLuint id = Resources::ResourcesManager::GetTexture("resources/Images/Blocks/blocks2.png", false);
	for (unsigned int i = 0; i < craft.GetSize(); i++)
	{
		ImGui::PushID(i);
		if ((i % 3) != 0)
		{
			spacingX++;
			ImGui::SameLine();
		}
		else
		{
			spacingX = 0;//hieghtStart ------------  Espacement Height
			spacingY++;
			ImGui::SetCursorPosY((height * 0.186f) + (height * 0.075f * spacingY));
		}

		ImGui::SetCursorPos(ImVec2(width * 0.37f + spacingX * (width * 0.048f), ImGui::GetCursorPosY()));
		ImVec2 cursor = ImGui::GetCursorPos();

		/*Calcul Texel*/
		float itemTexture = (float)craft.GetItem(i);
		int y = (int)(itemTexture * 0.1f);
		int x = (int)itemTexture % 10;
		ImGui::ImageButton((void*)(intptr_t)id, ImVec2(width * 0.0336f, height * 0.0525f), { 0.1f * x, 0.f + 0.1f * y }, { 0.1f * x + 0.1f, 0.1f + 0.1f * y });

		ImGuiDragDropFlags src_flags = 0;
		src_flags |= ImGuiDragDropFlags_SourceNoDisableHover;     // Keep the source displayed as hovered
		src_flags |= ImGuiDragDropFlags_SourceNoHoldToOpenOthers; // Because our dragging is local, we disable the feature of opening foreign treenodes/tabs while dragging
		if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID))
		{
			m_currentDrag = DragArray::CRAFT;

			ImGui::SetDragDropPayload("DragAndDropArray", &i, sizeof(unsigned int));
			ImGui::ImageButton((void*)(intptr_t)id, ImVec2(width * 0.0336f, height * 0.0525f), { 0.1f * x, 0.f + 0.1f * y }, { 0.1f * x + 0.1f, 0.1f + 0.1f * y });
			ImGui::EndDragDropSource();
		}
		if (ImGui::BeginDragDropTarget())
		{
			ImGuiDragDropFlags target_flags = 0;
			target_flags |= ImGuiDragDropFlags_AcceptBeforeDelivery;    // Don't wait until the delivery (release mouse button on a target) to do something
			target_flags |= ImGuiDragDropFlags_AcceptNoDrawDefaultRect; // Don't display the yellow rectangle
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DragAndDropArray", target_flags))
			{
				IM_ASSERT(payload->DataSize == sizeof(unsigned int));
				unsigned int payload_n = *(const unsigned int*)payload->Data;

				if (ImGui::IsMouseReleased(ImGuiMouseButton_Left))
				{
					if (m_currentDrag == DragArray::INVENTORY)
					{
						//Inventory to craft
						App::GetGameManager().MutateInventoryManager().InteractionInventoryToCraft(inventory, payload_n, craft,i);
					}
					if (m_currentDrag == DragArray::CRAFT)
					{
						App::GetGameManager().MutateInventoryManager().CraftInteractions(craft, i, payload_n);
					}
				}
			}
			ImGui::EndDragDropTarget();
		}
		ImGui::PopID();

		std::string text = std::to_string(craft.GetItemQuantity(i));
		ImGui::SetCursorPos(cursor);
		ImGui::Text(text.c_str());

	}
}

void UI::DragAndDropCraftingResult(const float width, const float height, InventoryComponent& result)
{
	float itemTexture = (float)result.GetItem(0);
	int y = (int)(itemTexture * 0.1f);
	int x = (int)itemTexture % 10;
	GLuint id = Resources::ResourcesManager::GetTexture("resources/Images/Blocks/blocks3.png", false);
	for (unsigned int i = 0; i <= result.GetSize(); i++)
	{
		ImGui::PushID(i);
		ImGui::SetCursorPos(ImVec2(width * 0.6469f, height * 0.339f));
		ImVec2 cursor = ImGui::GetCursorPos();
		ImGui::ImageButton((void*)(intptr_t)id, ImVec2(width * 0.0336f, height * 0.0525f), { 0.1f * x, 0.f + 0.1f * y }, { 0.1f * x + 0.1f, 0.1f + 0.1f * y });

		ImGuiDragDropFlags src_flags = 0;
		src_flags |= ImGuiDragDropFlags_SourceNoDisableHover;     // Keep the source displayed as hovered
		src_flags |= ImGuiDragDropFlags_SourceNoHoldToOpenOthers; // Because our dragging is local, we disable the feature of opening foreign treenodes/tabs while dragging
		if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID))
		{
			m_currentDrag = DragArray::CRAFTING_RESULT;
			ImGui::SetDragDropPayload("DragAndDropArray", &i, sizeof(unsigned int));
			ImGui::ImageButton((void*)(intptr_t)id, ImVec2(width * 0.0336f, height * 0.0525f), { 0.1f * x, 0.f + 0.1f * y }, { 0.1f * x + 0.1f, 0.1f + 0.1f * y });
			ImGui::EndDragDropSource();
		}
		ImGui::PopID();
	}
	/*std::string text = std::to_string(1);
	ImGui::SetCursorPos(cursor);
	ImGui::Text(text.c_str());*/
}

void UI::InitFont()
{
	ImGuiIO& io = ImGui::GetIO();
	m_normalFont = io.Fonts->AddFontFromFileTTF("resources/Fonts/Minecraft.ttf", 12.f);
	m_bigFont = io.Fonts->AddFontFromFileTTF("resources/Fonts/Minecraft.ttf", 48.f);
}
