#pragma once
#include "State.h"
#include "GLFW/glfw3.h"
class FSM
{
public:
	FSM();
	~FSM();

	GameState GetState()const;
	State& GetFunction(GameState state);
	void ChangeState(GameState state, GLFWwindow* window);
	void Update(GLFWwindow* window, const int windowWidth, const int windowHeight, const float deltaTime);

private:
	State* m_state[(int)GameState::NO_STATE];
	State* m_currentState = nullptr;
};