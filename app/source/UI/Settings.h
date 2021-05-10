#pragma once
#include "State.h"
#include "InputManager.h"

#pragma warning(push)
#pragma warning(disable:26495)
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#pragma warning(pop)

class Settings
{
public:
	Settings() = default;
	~Settings() = default;
	bool Run(const float windowWidth,const float windowHeight, GLFWwindow* window);
	static void PopWindow();
private:
	bool DisplayWindow(const float windowWidth, const float windowHeight);
	void ConfigWindow(const float windowWidth, const float windowHeight);
	bool ButtonReturn(const float windowWidth, const float windowHeight);

	void ConfigPlayer(const float windowWidth, const float windowHeight);
	void ButtonForward(const float windowWidth, const float windowHeight);
	void ButtonBackward(const float windowWidth, const float windowHeight);
	void ButtonRight(const float windowWidth, const float windowHeight);
	void ButtonLeft(const float windowWidth, const float windowHeight);
	void ButtonJump(const float windowWidth, const float windowHeight);
	void SliderSensitivity(const float windowWidth, const float windowHeight);
	void SliderFOV(const float windowWidth, const float windowHeight);
	void VolumeMenu(const float windowWidth, const float windowHeight);
	void VolumeGame(const float windowWidth, const float windowHeight);
	void VolumeEnemy(const float windowWidth, const float windowHeight);
	

			/*SETTINGS VARIABLE*/
	//UI
	static bool m_popWindow;
	ImVec2 m_buttonSize = { 0.f, 0.f };
	ImVec2 m_buttonPos = {0.f,0.f};

	//Camera
	float m_mouseSensitivity = 0.02f;
	float m_FOV = 90.f;

	//Volume
	float m_volumeMenu = 0.6f;
	float m_volumeGame = 0.6f;
	float m_volumeEnemy = 0.6f;

	//Key
	int m_keycode;
	const char* m_keyName = nullptr;
	const char* VerifyKey(InputManager::KeyAction action);
};
