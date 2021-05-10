#pragma once

struct GLFWwindow;

enum class GameState
{
	MENU = 0,
	PLAY,
	NO_STATE //keep this entry last
};

class State
{
public:
	State() = default;
	State(const State& other) = delete;
	State& operator=(const State&& other) = delete;
	virtual ~State() = default;

	virtual GameState GetState() const = 0;
	virtual void OnBegin(GLFWwindow* window) = 0;
	virtual GameState OnUpdate(GLFWwindow* window, const int windowWidth, const int windowHeight, const float deltaTime) = 0;
	virtual void OnEnd() = 0;
};