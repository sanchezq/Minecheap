#pragma once
#include "State.h"
#include "Maths/vec4.h"
#include "SoundManager.h"
#include  <irrKlang.h>


class StatePlay : public State
{

public:
	StatePlay();
	~StatePlay();

	GameState GetState() const override { return GameState::PLAY; }
	virtual GameState OnUpdate(GLFWwindow* window, const int windowWidth, const int windowHeight, const float deltaTime) override;
	virtual void OnEnd() override;
	void OnBegin(GLFWwindow* window) override;
	//void MoveCamera(LowRenderer::MovCamera& dir);

	float m_gameMusicVolume = 0.6f;
	float m_volumeEnemies = 0.6f;
	irrklang::ISound* m_sound = nullptr;
private:
	GameState m_currentState = GameState::PLAY;

	/*Game UI Functions*/
	void GameUI(const float width, const float height);
	void ConfigWindowGameUI(const float width, const float height);
	void DisplayCrossHair(const float width, const float height, const char* path);
	void DisplayLifePlayer(const float width, const float height, const char* path);
	void DisplayHotBar(const float width, const float height);

	/*Pause UI Functions*/
	bool m_pause = false;
	void PauseGame(GLFWwindow* window, const int windowWidth, const int windowHeight);
	void ConfigWindowPause(const float width, const float height);
	void ButtonResume(const float width, const float height);
	void ButtonOptions(const float width, const float height);
	void ButtonMenu(const float width, const float height);
	void ButtonSaveAndQuit(const float width, const float height);

	/*Death UI Functions*/
	void ConfigWindowDeath(const float width, const float height);
	void DisplayDeathScreen(const float width, const float height);
	/*Inventory*/
	void DisplayInventory(const float width, const float height);

	/*WaterUI*/
	void WaterUI(const float width, const float height);
	bool m_waterUI = false;

	float m_delta = 0.f;

};