#include "Settings.h"

#pragma warning(push)
#pragma warning(disable:26495)
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#pragma warning(pop)
#include "GameManager.h"
#include "GLFW/glfw3.h"
#include "ResourceGFX.h"//clearWindow
#include "App.h"
#include <iostream>
#include "StateMenu.h"
#include "StatePlay.h"

//Init Static
bool Settings::m_popWindow = false;

bool Settings::Run(float windowWidth, float windowHeight, GLFWwindow* window)
{
	m_buttonSize = { windowWidth * 0.08f, windowHeight * 0.025f };

	//Init
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	App::GetGameManager().MutateUI().m_countPush = 0;

	if (m_popWindow)
	{
		ImGui::SetNextWindowPos(ImVec2(0, 0));
		ImGui::SetNextWindowSize(ImVec2(windowWidth, windowHeight));
		ImGui::Begin("WindowPOP", &m_popWindow, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

		ImGui::SetCursorPos(ImVec2(windowWidth * 0.5f - 25.f, windowHeight * 0.5f));
		ImGui::Text("Input already assigned:");
		ImGui::SetCursorPos(ImVec2(windowWidth * 0.5f, windowHeight * 0.5413f));
		if (ImGui::Button("OK", m_buttonSize))
		{
			m_popWindow = false;
		}
		ImGui::End();
	}

	return DisplayWindow(windowWidth, windowHeight);
}

void Settings::PopWindow()
{
	m_popWindow = true;
}

bool Settings::DisplayWindow(const float width, const float height)
{
	ConfigWindow(width, height);
	ConfigPlayer(width, height);
	SliderSensitivity(width, height);
	SliderFOV(width, height);
	VolumeMenu(width, height);
	VolumeGame(width, height);
	VolumeEnemy(width, height);
	bool setting = ButtonReturn(width, height);
	ImGui::PopStyleColor(App::GetGameManager().MutateUI().m_countPush);
	ImGui::End();

	return setting;
}

bool Settings::ButtonReturn(const float windowWidth, const float windowHeight)
{
	m_buttonPos = { windowWidth * 0.5f, windowHeight * 0.8928f };

	if (App::GetGameManager().MutateUI().Button(m_buttonPos.x, m_buttonPos.y, m_buttonSize.x, m_buttonSize.y, "resources/Images/Menu/Button6.jpg", "Return"))
	{
		return false;
	}
	return true;
}

void Settings::ConfigWindow(const float windowWidth, const float windowHeight)
{
	bool settings = true;
	ImGui::SetNextWindowPos(ImVec2(-5, -2));
	ImGui::SetNextWindowSize({ windowWidth + 25, windowHeight + 20 });
	ImGui::Begin("Settings", &settings, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

	ImGui::SetCursorPos({ 1,0 });
	GLuint my_image_texture = Resources::ResourcesManager::GetTexture("resources/Images/Menu/dirtWallpaper.png", false);
	ImGui::Image((void*)(intptr_t)my_image_texture, ImVec2(windowWidth + 20, windowHeight + 20));

	ImGui::SetCursorPos({ 6,1 });
	if (App::GetGameManager().GetInputManager().m_ChangeKey)
	{
		ImGui::Text("Press one Key:");
	}
}

void Settings::ConfigPlayer(const float windowWidth, const float windowHeight)
{
	ButtonForward(windowWidth, windowHeight);
	ButtonBackward(windowWidth, windowHeight);
	ButtonRight(windowWidth, windowHeight);
	ButtonLeft(windowWidth, windowHeight);
	ButtonJump(windowWidth, windowHeight);
}

void Settings::ButtonForward(const float windowWidth, const float windowHeight)
{
	ImGui::SetCursorPos(ImVec2(windowWidth * 0.35f, windowHeight * 0.06f));
	ImGui::Text("Move Player Foward:");

	m_keyName = VerifyKey(InputManager::KeyAction::MOVE_PLAYER_FORWARD);
	m_buttonPos = { windowWidth * 0.35f, windowHeight * 0.083f };

	if (App::GetGameManager().MutateUI().Button(m_buttonPos.x, m_buttonPos.y, m_buttonSize.x, m_buttonSize.y, "resources/Images/Menu/Button.jpg", m_keyName))
	{
		App::GetGameManager().MutateInputManager().m_ChangeKey = true;
		App::GetGameManager().MutateInputManager().SetKeyChange(InputManager::KeyAction::MOVE_PLAYER_FORWARD);
	}
}

void Settings::ButtonBackward(const float windowWidth, const float windowHeight)
{
	ImGui::SetCursorPos(ImVec2(windowWidth * 0.35f, windowHeight * 0.18f));
	ImGui::Text("Move Player Backward:");

	m_keyName = VerifyKey(InputManager::KeyAction::MOVE_PLAYER_BACKWARD);
	m_buttonPos = { windowWidth * 0.35f, windowHeight * 0.2f };

	if (App::GetGameManager().MutateUI().Button(m_buttonPos.x, m_buttonPos.y, m_buttonSize.x, m_buttonSize.y, "resources/Images/Menu/Button2.jpg", m_keyName))
	{
		App::GetGameManager().MutateInputManager().m_ChangeKey = true;
		App::GetGameManager().MutateInputManager().SetKeyChange(InputManager::KeyAction::MOVE_PLAYER_BACKWARD);
	}
}

void Settings::ButtonRight(const float windowWidth, const float windowHeight)
{
	ImGui::SetCursorPos(ImVec2(windowWidth * 0.35f, windowHeight * 0.28f));
	ImGui::Text("Move Player Right:");

	m_keyName = VerifyKey(InputManager::KeyAction::MOVE_PLAYER_RIGHT);
	m_buttonPos = { windowWidth * 0.35f, windowHeight * 0.3f };

	if (App::GetGameManager().MutateUI().Button(m_buttonPos.x, m_buttonPos.y, m_buttonSize.x, m_buttonSize.y, "resources/Images/Menu/Button3.jpg", m_keyName))
	{
		App::GetGameManager().MutateInputManager().m_ChangeKey = true;
		App::GetGameManager().MutateInputManager().SetKeyChange(InputManager::KeyAction::MOVE_PLAYER_RIGHT);
	}
}

void Settings::ButtonLeft(const float windowWidth, const float windowHeight)
{
	ImGui::SetCursorPos(ImVec2(windowWidth * 0.35f, windowHeight * 0.38f));
	ImGui::Text("Move Player Left:");

	m_keyName = VerifyKey(InputManager::KeyAction::MOVE_PLAYER_LEFT);
	m_buttonPos = { windowWidth * 0.35f, windowHeight * 0.4f };

	if (App::GetGameManager().MutateUI().Button(m_buttonPos.x, m_buttonPos.y, m_buttonSize.x, m_buttonSize.y, "resources/Images/Menu/Button4.jpg", m_keyName))
	{
		App::GetGameManager().MutateInputManager().m_ChangeKey = true;
		App::GetGameManager().MutateInputManager().SetKeyChange(InputManager::KeyAction::MOVE_PLAYER_LEFT);
	}
}

void Settings::ButtonJump(const float windowWidth, const float windowHeight)
{
	ImGui::SetCursorPos(ImVec2(windowWidth * 0.35f, windowHeight * 0.48f));
	ImGui::Text("Player Jump:");

	m_keyName = VerifyKey(InputManager::KeyAction::PLAYER_JUMP);
	m_buttonPos = { windowWidth * 0.35f, windowHeight * 0.5f };

	if (App::GetGameManager().MutateUI().Button(m_buttonPos.x, m_buttonPos.y, m_buttonSize.x, m_buttonSize.y, "resources/Images/Menu/Button5.jpg", m_keyName))
	{
		App::GetGameManager().MutateInputManager().m_ChangeKey = true;
		App::GetGameManager().MutateInputManager().SetKeyChange(InputManager::KeyAction::PLAYER_JUMP);
	}
}

void Settings::SliderSensitivity(const float windowWidth, const float windowHeight)
{
	ImGui::SetCursorPos(ImVec2(windowWidth * 0.65f, windowHeight * 0.06f));
	ImGui::Text("Mouse Sensitivity");
	ImGui::SetCursorPos(ImVec2(windowWidth * 0.65f, windowHeight * 0.083f));
	ImGui::PushItemWidth(110);
	ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, { 0,1,0,1 });
	ImGui::SliderFloat("", &m_mouseSensitivity, 0.f, 1.f);
	ImGui::PopStyleColor();
	App::GetGameManager().MutateScene().m_camera.m_sensitivity = m_mouseSensitivity;
}

void Settings::SliderFOV(const float windowWidth, const float windowHeight)
{
	ImGui::SetCursorPos(ImVec2(windowWidth * 0.65f, windowHeight * 0.18f));
	ImGui::Text("Camera FOV");
	ImGui::SetCursorPos(ImVec2(windowWidth * 0.65f, windowHeight * 0.2f));
	ImGui::PushItemWidth(110);
	ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, { 0,1,0,1 });
	ImGui::SliderFloat(" ", &m_FOV, 30.f, 110.f);
	ImGui::PopStyleColor();
	App::GetGameManager().MutateScene().m_camera.m_fov = m_FOV;
	App::GetGameManager().MutateScene().UpdateProjectionMatrix();
}

void Settings::VolumeMenu(const float windowWidth, const float windowHeight)
{
	ImGui::SetCursorPos(ImVec2(windowWidth * 0.65f, windowHeight * 0.28f));
	ImGui::Text("Volume Menu");
	ImGui::SetCursorPos(ImVec2(windowWidth * 0.65f, windowHeight * 0.3f));
	ImGui::PushItemWidth(110);
	ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, { 0,1,0,1 });
	ImGui::SliderFloat("  ", &m_volumeMenu, 0.f, 1.f);
	ImGui::PopStyleColor();
	StateMenu& menu = (StateMenu&)(App::GetGameManager().MutateFSM().GetFunction(GameState::MENU));
	menu.m_soundVolume = m_volumeMenu;
	App::GetGameManager().MutateSound().Volume(menu.m_soundMenu, menu.m_soundVolume);
	App::GetGameManager().MutateSound().VolumeInitBackground(menu.m_soundVolume);
}

void Settings::VolumeGame(const float windowWidth, const float windowHeight)
{
	ImGui::SetCursorPos(ImVec2(windowWidth * 0.65f, windowHeight * 0.38f));
	ImGui::Text("Volume Game");
	ImGui::SetCursorPos(ImVec2(windowWidth * 0.65f, windowHeight * 0.4f));
	ImGui::PushItemWidth(110);
	ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, { 0,1,0,1 });
	ImGui::SliderFloat("   ", &m_volumeGame, 0.f, 1.f);
	ImGui::PopStyleColor();

	StatePlay& game = (StatePlay&)(App::GetGameManager().MutateFSM().GetFunction(GameState::PLAY));
	game.m_gameMusicVolume = m_volumeGame;
	App::GetGameManager().MutateSound().Volume(game.m_sound, game.m_gameMusicVolume);
}

void Settings::VolumeEnemy(const float windowWidth, const float windowHeight)
{
	ImGui::SetCursorPos(ImVec2(windowWidth * 0.65f, windowHeight * 0.48f));
	ImGui::Text("Volume Enemy");
	ImGui::SetCursorPos(ImVec2(windowWidth * 0.65f, windowHeight * 0.5f));
	ImGui::PushItemWidth(110);
	ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, { 0,1,0,1 });
	ImGui::SliderFloat("    ", &m_volumeEnemy, 0.f, 1.f);
	ImGui::PopStyleColor();

	StatePlay& game = (StatePlay&)(App::GetGameManager().MutateFSM().GetFunction(GameState::PLAY));
	game.m_volumeEnemies = m_volumeEnemy;
	if (App::GetGameManager().MutateWorld().m_zombie != nullptr)
	{
		App::GetGameManager().MutateSound().Volume(App::GetGameManager().MutateWorld().m_zombie->m_sound, game.m_volumeEnemies);
	}
}

const char* Settings::VerifyKey(InputManager::KeyAction action)
{
	m_keycode = App::GetGameManager().GetInputManager().GetMap().find(action)->second;
	switch (m_keycode)
	{
	case 32:
		return "Space";
		break;
	case 262:
		return "Arrow_Right";
		break;
	case 263:
		return "Arrow_Left";
		break;
	case 264: 
		return "Arrow_Down";
		break;
	case 265:
		return "Arrow_UP";
		break;
	case 290:
		return "F1";
		break;
	case 291:
		return "F2";
		break;
	case 292:
		return "F3";
		break;
	case 293:
		return "F4";
		break;
	case 294:
		return "F5";
		break;
	case 295:
		return "F6";
		break;
	case 296:
		return "F7";
		break;
	case 297:
		return "F8";
		break;
	case 298:
		return "F9";
		break;
	case 299:
		return "F10";
		break;
	case 300:
		return "F11";
		break;
	case 301:
		return "F12";
		break;
	default:
		if (glfwGetKeyName(m_keycode, 0) == NULL)
		{
			App::GetGameManager().GetInputManager().GetMap()[action] = GLFW_KEY_UNKNOWN;
			/* 
			const char* result = "null";
			for (size_t i = 0; i < (int)action; i++)
			{
				result += ' ';
			}*/
			return "null";
		}
		return glfwGetKeyName(m_keycode, 0);
		break;
	}
}
