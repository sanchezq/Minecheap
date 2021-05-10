#pragma once

struct GLFWWindow;

#include "InputManager.h"
#include "FSM.h"
#include "Settings.h"
#include "SaveXML.h"
#include "World.h"
#include "Resources/Scene.h"
#include "CameraSettings.h"
#include "UI.h"
#include "BlockDataBase.h"
#include "ItemDataBase.h"
#include "InventoryManager.h"
#include "SoundManager.h"

class GameManager
{
public:
	GameManager() = default;
	GameManager(const GameManager& other) = delete;
	GameManager& operator=(const GameManager& other) = default;
	~GameManager() = default;

	bool Initialize(GLFWwindow* window, Resources::Scene& scene);

	void Update(GLFWwindow* window, const int windowWidth, const int windowHeight, const float deltaTime);

	// UI
	void SetIsPauseUI(bool pause);
	const bool GetIsPauseUI() const;
	void SetInInventory(bool pause);
	const bool GetInInventory() const;
	void SetIsSettingsUI(bool inSetting);
	const bool GetIsSettingsUI() const;

	// Get and Mutate
	const InputManager& GetInputManager() const;
	InputManager& MutateInputManager();
	const FSM& GetFSM() const;
	FSM& MutateFSM();
	const World& GetWorld() const;
	World& MutateWorld();
	const Settings& GetSettings() const;
	Settings& MutateSettings();
	const Resources::Scene& GetScene() const;
	Resources::Scene& MutateScene();
	const UI& GetUI() const;
	UI& MutateUI();
	const SoundManager& GetSound() const;
	SoundManager& MutateSound();
	const BlockDataBase& GetBlockDataBase() const;
	BlockDataBase& MutateBlockDataBase();

	const ItemDataBase& GetItemDataBase() const;
	ItemDataBase& MutateItemDataBase();

	const InventoryManager& GetInventoryManager() const;
	InventoryManager& MutateInventoryManager();
	
	void SaveGame();
	void LoadGame();

	//camera settings
	CameraSettings m_cameraSettings;

private:
	Resources::Scene* m_scene = nullptr;
	World m_world;
	UI m_ui;
	SoundManager m_sound;
	Settings m_settings;
	
	SaveXML m_save;
	InputManager m_inputManager;
	FSM m_fsm;

	BlockDataBase m_blockDatas;
	ItemDataBase m_itemDatas;
	InventoryManager m_inventory;


	// UI
	//Todo: UI Manager/ Enums ?
	bool m_isPauseUI = false;
	bool m_isSettingsUI = false;
	bool m_inInventory = false;
};