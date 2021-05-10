#include "FSM.h"
#include "StatePlay.h"
#include "StateMenu.h"

FSM::FSM()
{
	m_state[(int)GameState::MENU] = new StateMenu();
	m_state[(int)GameState::PLAY] = new StatePlay();

	m_currentState = m_state[(int)GameState::MENU];
}

FSM::~FSM()
{
	for (int nbState = 0; nbState < (int)GameState::NO_STATE; nbState++)
	{
		delete m_state[nbState];
	}
}

GameState FSM::GetState() const
{
	return m_currentState->GetState();
}

State& FSM::GetFunction(GameState state)
{
	return *m_state[(int)state];
}

void FSM::ChangeState(GameState state, GLFWwindow* window)
{
	m_currentState->OnEnd();
	m_currentState = m_state[(int)state];
	m_currentState->OnBegin(window);
}

void FSM::Update(GLFWwindow* window, const int windowWidth, const int windowHeight, const float deltaTime)
{
	GameState next = m_currentState->OnUpdate(window, windowWidth, windowHeight, deltaTime);
	if (next != m_currentState->GetState())
	{
		ChangeState(next, window);
	}
}