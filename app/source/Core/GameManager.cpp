#include "GameManager.h"

#include <GLFW/glfw3.h>
#include "Resources/Scene.h"
#pragma warning(push)
#pragma warning(disable:26495)
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#pragma warning(pop)
#include "SaveXML.h"

bool GameManager::Initialize(GLFWwindow* window, Resources::Scene& scene)
{
	if (window == nullptr)
	{
		return false;
	}
	
	m_scene = &scene;
	m_world.Initialize(m_scene);

	m_inputManager.InitializeWindowCallBack(window);
	MutateSound().BackgroundMusicInit("resources/Sounds/menu.ogg", true);
	return true;
}

void GameManager::Update(GLFWwindow* window, const int windowWidth, const int windowHeight, const float deltaTime)
{

	//--- Set new Frame for ImGUI ---//
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();

	ImGui::NewFrame();

	/*Poll for and process events*/
	glfwPollEvents();

	if (GetIsPauseUI())
	{
		m_inputManager.ProcessInput(window, 0);
		m_fsm.Update(window, windowWidth, windowHeight, 0);
	}
	else
	{
		m_inputManager.ProcessInput(window, deltaTime);
		m_fsm.Update(window, windowWidth, windowHeight, deltaTime);
	}

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GameManager::SetIsPauseUI(bool pause)
{
	m_isPauseUI = pause;
}

const bool GameManager::GetIsPauseUI() const
{
	return m_isPauseUI;
}

void GameManager::SetInInventory(bool inInventory)
{
	m_inInventory = inInventory;
}

const bool GameManager::GetInInventory() const
{
	return m_inInventory;
}

void GameManager::SetIsSettingsUI(bool inSetting)
{
	m_isSettingsUI = inSetting;
}

const bool GameManager::GetIsSettingsUI() const
{
	return m_isSettingsUI;
}

const InputManager& GameManager::GetInputManager() const
{
	return m_inputManager;
}

InputManager& GameManager::MutateInputManager()
{
	return m_inputManager;
}

const FSM& GameManager::GetFSM() const
{
	return m_fsm;
}

FSM& GameManager::MutateFSM()
{
	return m_fsm;
}

const World& GameManager::GetWorld() const
{
	return m_world;
}

World& GameManager::MutateWorld()
{
	return m_world;
}

const Settings& GameManager::GetSettings() const
{
	return m_settings;
}

Settings& GameManager::MutateSettings()
{
	return m_settings;
}

const Resources::Scene& GameManager::GetScene() const
{
	return *m_scene;
}

Resources::Scene& GameManager::MutateScene()
{
	return *m_scene;
}

const UI& GameManager::GetUI() const
{
	return m_ui;
}

UI& GameManager::MutateUI()
{
	return m_ui;
}

const SoundManager& GameManager::GetSound() const
{
	return m_sound;
}

SoundManager& GameManager::MutateSound()
{
	return m_sound;
}

const BlockDataBase& GameManager::GetBlockDataBase() const
{
	return m_blockDatas;
}

BlockDataBase& GameManager::MutateBlockDataBase()
{
	return m_blockDatas;
}

const ItemDataBase& GameManager::GetItemDataBase() const
{
	return m_itemDatas;
}

ItemDataBase& GameManager::MutateItemDataBase()
{
	return m_itemDatas;
}

const InventoryManager& GameManager::GetInventoryManager() const
{
	return m_inventory;
}

InventoryManager& GameManager::MutateInventoryManager()
{
	return m_inventory;
}

void GameManager::SaveGame()
{
	m_save.ExportSave("saves/save-2.xml",  m_world);
}

void GameManager::LoadGame()
{
	m_save.CheckError(m_save.ImportSave("saves/save-2.xml", m_world));	
}
