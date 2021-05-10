#include "StateMenu.h"
#include "ResourceGFX.h"
#include "GameManager.h"
#include "Resources/ResourcesManager.h"

#pragma warning(push)
#pragma warning(disable:26495)
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#pragma warning(pop)
#include "Resources/TextureManager.h"
#include <iostream>
#include "App.h"

StateMenu::~StateMenu()
{
	if (m_soundMenu != nullptr)
	{
		m_soundMenu->drop();
	}
}

void StateMenu::OnBegin(GLFWwindow* window)
{
				//--- Render Cursor ---//
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	m_soundMenu = App::GetGameManager().MutateSound().Play2D("resources/Sounds/menu.ogg", true);
	App::GetGameManager().MutateSound().Volume(m_soundMenu, m_soundVolume);
	m_currentState = GameState::MENU;
}

GameState StateMenu::OnUpdate(GLFWwindow* window, const int windowWidth, const int windowHeight, const float /*deltaTime*/)
{
	App::GetGameManager().MutateUI().m_countPush = 0;

	//--- GlClear ---//
	ClearWindow(m_color);

	if (App::GetGameManager().GetIsSettingsUI())
	{
		App::GetGameManager().SetIsSettingsUI(App::GetGameManager().MutateSettings().Run((float)windowWidth, (float)windowHeight, window));
	}
	else if (m_displaySave)
	{
		DisplaySaves((float)windowWidth, (float)windowHeight, m_displaySave);
	}
	else
	{
		DisplayWindow((float)windowWidth, (float)windowHeight, window);
	}

	return m_currentState;
}

void StateMenu::DisplayWindow(const float width, const float height, GLFWwindow* window)
{
	ConfigWindow(width, height); 

	m_buttonSizeX = width * 0.13636f;
	m_buttonSizeY = height * 0.0357f;
	ButtonPlay(width, height);
	ButttonLoadSaves(width, height);
	ButtonOptions(width, height);
	ButtonQuit(width, height, window); 

	ImGui::PopStyleColor(App::GetGameManager().MutateUI().m_countPush);

	ImGui::End(); 
}

void StateMenu::ConfigWindow(const float width, const float height)
{
	bool menu = true;
	ImGui::SetNextWindowPos(ImVec2(-5, -2));
	ImGui::SetNextWindowSize({ width + 20, height + 20 });
	ImGui::Begin("MENU", &menu, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
	
	ImGui::SetCursorPos({ 1,0 });

	GLuint my_image_texture = Resources::ResourcesManager::GetTexture("resources/Images/Menu/fondMine.jpg", false);
	ImGui::Image((void*)(intptr_t)my_image_texture, ImVec2(width + 20, height + 20));
}

void StateMenu::ButtonPlay(const float width, const float height)
{
	//---- Button NEW Game ----//
	float buttonPosX = width * 0.455f;
	float buttonPosY = height * 0.417f;
	if(App::GetGameManager().MutateUI().Button(buttonPosX, buttonPosY, m_buttonSizeX, m_buttonSizeY,"resources/Images/Menu/Button.jpg", "SINGLEPLAYER"))
	{
		App::GetGameManager().MutateWorld().InitNewGame();
		m_currentState = GameState::PLAY;
	}
}

void StateMenu::ButttonLoadSaves(const float width, const float height)
{
	float buttonPosX = width * 0.455f;
	float buttonPosY = height * 0.5f;
	if(App::GetGameManager().MutateUI().Button(buttonPosX, buttonPosY, m_buttonSizeX, m_buttonSizeY, "resources/Images/Menu/Button2.jpg", "Load Game"))
	{
		App::GetGameManager().MutateWorld().LoadSave();
		m_currentState = GameState::PLAY;
		//m_displaySave = true;
	}
}

void StateMenu::ButtonOptions(const float width, const float height)
{
	//---- Button Options ----//
	float buttonPosX = width * 0.455f;
	float buttonPosY = height * 0.583f;
	if(App::GetGameManager().MutateUI().Button(buttonPosX, buttonPosY, m_buttonSizeX, m_buttonSizeY, "resources/Images/Menu/Button4.jpg", "SETTINGS"))
	{
		App::GetGameManager().SetIsSettingsUI(true);
	}
}

void StateMenu::ButtonQuit(const float width, const float height, GLFWwindow* window)
{
	//---- Button QUIT ----//
	float buttonPosX = width * 0.455f;
	float buttonPosY = height * 0.6757f;
	if(App::GetGameManager().MutateUI().Button(buttonPosX, buttonPosY, m_buttonSizeX, m_buttonSizeY, "resources/Images/Menu/Button3.jpg", "QUIT"))
	{
		glfwSetWindowShouldClose(window, true);
	}
}

void StateMenu::DisplaySaves(const float width, const float height, bool& display)
{
	//TODO : List Saves for multiple save
	ConfigWindowSave(width, height);
	
	ButtonReturn(width, height, display);

	ImGui::PopStyleColor(App::GetGameManager().MutateUI().m_countPush);

	ImGui::End();
}

void StateMenu::ConfigWindowSave(const float width, const float height)
{
	bool loadGame = true;
	ImGui::SetNextWindowPos(ImVec2(-5, -2));
	ImGui::SetNextWindowSize({ width + 20, height + 20 });
	ImGui::Begin("Settings", &loadGame, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

	ImGui::SetCursorPos({ 1,0 });
	GLuint my_image_texture = Resources::ResourcesManager::GetTexture("resources/Images/Menu/dirtWallpaper.png", false);
	ImGui::Image((void*)(intptr_t)my_image_texture, ImVec2(width + 20, height + 20));
}

void StateMenu::SelectSave(const float width, const float height)
{
	if( App::GetGameManager().MutateUI().Button(width * 0.455f, height * 0.5f, width * 0.136f, height * 0.0357f, "resources/Images/Menu/Button2.jpg", "Select Save"))
	{
		//todo
	}
}

bool StateMenu::ButtonReturn(const float width, const float height, bool& display)
{
	if(App::GetGameManager().MutateUI().Button(width * 0.455f, height * 0.4166f, width * 0.136f, height * 0.0357f, "resources/Images/Menu/Button.jpg", "RETURN"))
	{
		display = false;
	}
	return display;
}

void StateMenu::OnEnd()
{
	App::GetGameManager().MutateSound().StopAllMusics();
}
	