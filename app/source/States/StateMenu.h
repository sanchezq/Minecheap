#pragma once
#include "State.h"
#include "Maths/vec4.h"
#include "GLFW/glfw3.h"
#include "SoundManager.h"
#pragma warning(push)
#pragma warning(disable:26495)
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#pragma warning(pop)
#include "UI.h"

class StateMenu : public State
{
public:
	StateMenu() = default;
	~StateMenu();

	GameState GetState() const override { return GameState::MENU; }
	virtual GameState OnUpdate(GLFWwindow* window, const int windowWidth, const int windowHeight, const float deltaTime) override;
	virtual void OnEnd() override;
	void OnBegin(GLFWwindow* window) override;

	float  m_soundVolume = 0.6f;
	irrklang::ISound* m_soundMenu = nullptr;
private:
	Core::Maths::vec4 m_color{ 0.f,0.f,0.f,1.f };

	GameState m_currentState = GameState::MENU;
	void DisplayWindow(const float width, const float height, GLFWwindow* window);
	void ConfigWindow(const float width, const float height);
	void ButtonPlay(const float width, const float height);
	void ButtonOptions(const float width, const float height);
	void ButttonLoadSaves(const float width, const float height);
	void ButtonQuit(const float width, const float height, GLFWwindow* window);
	float m_buttonSizeX = 0.f;
	float m_buttonSizeY = 0.f;

	//TODO: deplacer ces function ?
	void DisplaySaves(const float width, const float height, bool& display);
	void ConfigWindowSave(const float width, const float height);
	void SelectSave(const float width, const float height);
	bool ButtonReturn(const float width, const float height, bool& display);
	bool m_displaySave = false;
};