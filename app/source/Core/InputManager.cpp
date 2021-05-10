#include "InputManager.h"
#include "LowRenderer/Camera.h"
#include "State.h"
#include "GameManager.h"
#include "Resources/Scene.h"
#include "Settings.h"
#include "App.h"
#include "Gameplay/Player.h"
#include "InventoryManager.h"
#include <iostream>

bool isLeftMouseClick = false;
bool isRightMouseClick = false;

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
InputManager::InputManager()
{
	m_settings[KeyAction::MOVE_CAMERA_FORWARD] = GLFW_KEY_UP;
	m_settings[KeyAction::MOVE_CAMERA_RIGHT] = GLFW_KEY_RIGHT;
	m_settings[KeyAction::MOVE_CAMERA_LEFT] = GLFW_KEY_LEFT;
	m_settings[KeyAction::MOVE_CAMERA_BACKWARD] = GLFW_KEY_DOWN;

	m_settings[KeyAction::MOVE_PLAYER_FORWARD] = GLFW_KEY_W;
	m_settings[KeyAction::MOVE_PLAYER_RIGHT] = GLFW_KEY_D;
	m_settings[KeyAction::MOVE_PLAYER_LEFT] = GLFW_KEY_A;
	m_settings[KeyAction::MOVE_PLAYER_BACKWARD] = GLFW_KEY_S;
	m_settings[KeyAction::PLAYER_JUMP] = GLFW_KEY_SPACE;
	m_settings[KeyAction::PLAYER_BREAK_BLOC] = GLFW_MOUSE_BUTTON_LEFT;
	m_settings[KeyAction::PLAYER_PLACE_BLOC] = GLFW_MOUSE_BUTTON_RIGHT;
	m_settings[KeyAction::INVENTORY] = GLFW_KEY_E;

} 

void InputManager::InitializeWindowCallBack(GLFWwindow* window)
{
	//callback for the scroll
	glfwSetScrollCallback(window, scroll_callback);

	//callback for the mouse
	glfwSetCursorPosCallback(window, mouse_callback);

	//callback for the inputs
	glfwSetKeyCallback(window, key_callback);
}

void InputManager::ProcessInput(GLFWwindow* window, float delta)
{	

	switch (App::GetGameManager().GetFSM().GetState())
	{
	case GameState::PLAY:
	{
		if (delta != 0 && !App::GetGameManager().GetInInventory())
		{
			if (glfwGetKey(window, m_settings[KeyAction::MOVE_PLAYER_FORWARD]) == GLFW_PRESS)
			{
				App::GetGameManager().MutateWorld().m_player.Move(PlayerMove::FORWARD, delta);
			}
			if (glfwGetKey(window, m_settings[KeyAction::MOVE_PLAYER_BACKWARD]) == GLFW_PRESS)
			{
				App::GetGameManager().MutateWorld().m_player.Move(PlayerMove::BACKWARD, delta);
			}
			if (glfwGetKey(window, m_settings[KeyAction::MOVE_PLAYER_LEFT]) == GLFW_PRESS)
			{
				App::GetGameManager().MutateWorld().m_player.Move(PlayerMove::LEFT, delta);
			}
			if (glfwGetKey(window, m_settings[KeyAction::MOVE_PLAYER_RIGHT]) == GLFW_PRESS)
			{
				App::GetGameManager().MutateWorld().m_player.Move(PlayerMove::RIGHT, delta);
			}
			if (glfwGetKey(window, m_settings[KeyAction::PLAYER_JUMP]) == GLFW_PRESS)
			{
				App::GetGameManager().MutateWorld().m_player.Move(PlayerMove::JUMP, delta);
			}
			if (glfwGetMouseButton(window, m_settings[KeyAction::PLAYER_BREAK_BLOC]) == GLFW_PRESS && !isLeftMouseClick)
			{
				App::GetGameManager().MutateWorld().m_player.BreakBlock();
				isLeftMouseClick = true;
			}
			if (glfwGetMouseButton(window, m_settings[KeyAction::PLAYER_BREAK_BLOC]) == GLFW_RELEASE && isLeftMouseClick)
			{
				isLeftMouseClick = false;
			}
			if (glfwGetMouseButton(window, m_settings[KeyAction::PLAYER_PLACE_BLOC]) == GLFW_PRESS && !isRightMouseClick)
			{
				App::GetGameManager().MutateWorld().m_player.PlaceBlock();
				isRightMouseClick = true;
			}
			if (glfwGetMouseButton(window, m_settings[KeyAction::PLAYER_PLACE_BLOC]) == GLFW_RELEASE && isRightMouseClick)
			{
				isRightMouseClick = false;
			}
		}
	}
	break;

	default:
		break;
	}
}

void InputManager::SetKeyChange(KeyAction key)
{
	m_keyChange = key;
}

InputManager::KeyAction InputManager::GetKeyChange() const
{
	return m_keyChange;
}

void InputManager::ChangeInput(KeyAction action, int key)
{
	for (int i = 0; i < (int)KeyAction::NOKEY; i++)
	{
		if (m_settings[(KeyAction)i] == key)
		{
			Settings::PopWindow();
			m_keyChange = action;
			return;
		}
	}
	m_settings[action] = key;
}

std::unordered_map<InputManager::KeyAction, int> InputManager::GetMap() const
{
	return m_settings;
}

void key_callback(GLFWwindow* window, int key, int /*scancode*/, int action, int /*mods*/)
{
	switch (App::GetGameManager().GetFSM().GetState())
	{
	case GameState::PLAY:
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		{
			App::GetGameManager().SetIsPauseUI(true);
		}
		if (key == GLFW_KEY_E && action == GLFW_PRESS)
		{
			if (App::GetGameManager().GetInInventory())
			{
				App::GetGameManager().MutateInventoryManager().ClearCraft(App::GetGameManager().MutateWorld().m_player.GetMutateInventory());
			}
			App::GetGameManager().SetInInventory(!(App::GetGameManager().GetInInventory()));
		}
		break;
	
	case GameState::MENU:
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		{
			exit(0);
		}
		break;

	default:
		break;
	}

	if (App::GetGameManager().GetInputManager().GetKeyChange() != InputManager::KeyAction::NOKEY)
	{
		App::GetGameManager().MutateInputManager().ChangeInput(App::GetGameManager().GetInputManager().GetKeyChange(), key);
		App::GetGameManager().MutateInputManager().SetKeyChange(InputManager::KeyAction::NOKEY);
	}
	else
	{
		App::GetGameManager().MutateInputManager().m_ChangeKey = false;
	}

	if (key == GLFW_KEY_F && action == GLFW_PRESS)
	{
		App::GetGameManager().m_cameraSettings.m_wireframe = !App::GetGameManager().m_cameraSettings.m_wireframe;
	}
	if (key == GLFW_KEY_G && action == GLFW_PRESS)
	{
		App::GetGameManager().m_cameraSettings.m_active_mouse = !App::GetGameManager().m_cameraSettings.m_active_mouse;
	}
	if (key == GLFW_KEY_M && action == GLFW_PRESS)
	{
		if (App::GetGameManager().m_cameraSettings.m_mouse_cursor == true)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			App::GetGameManager().m_cameraSettings.m_mouse_cursor = false;
		}
		else
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			App::GetGameManager().m_cameraSettings.m_mouse_cursor = true;
		}
	}
	if (key == GLFW_KEY_T && action == GLFW_PRESS)
	{
		App::GetGameManager().m_cameraSettings.m_transparency = !App::GetGameManager().m_cameraSettings.m_transparency;
		App::GetGameManager().MutateWorld().ForceUpdate();

		if (App::GetGameManager().m_cameraSettings.m_transparency)
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}
		else
		{
			glDisable(GL_BLEND);
		}
	}
}

void mouse_callback(GLFWwindow*, double xpos, double ypos)
{
	if (App::GetGameManager().GetFSM().GetState() == GameState::PLAY && !App::GetGameManager().GetIsPauseUI() && !App::GetGameManager().GetInInventory())
	{
		if (App::GetGameManager().m_cameraSettings.m_active_mouse)
		{
			if (App::GetGameManager().m_cameraSettings.m_firstMouse)
			{
				App::GetGameManager().m_cameraSettings.m_lastX = (float)xpos;
				App::GetGameManager().m_cameraSettings.m_lastY = (float)ypos;
				App::GetGameManager().m_cameraSettings.m_firstMouse = false;
			}

			float xoffset = (float)xpos - App::GetGameManager().m_cameraSettings.m_lastX;
			float yoffset = App::GetGameManager().m_cameraSettings.m_lastY - (float)ypos;

			App::GetGameManager().m_cameraSettings.m_lastX = (float)xpos;
			App::GetGameManager().m_cameraSettings.m_lastY = (float)ypos;

			App::GetGameManager().MutateScene().m_camera.MouseMoveCamera(xoffset, yoffset);
		}
	}
	else
	{
		//TODO #DEFINE
		App::GetGameManager().m_cameraSettings.m_lastX = 1250.f / 2.f;
		App::GetGameManager().m_cameraSettings.m_lastY = 600.f / 2.f;
	}
}

void scroll_callback(GLFWwindow* /*window*/, double /*xoffset*/, double yoffset)
{
	if (App::GetGameManager().GetFSM().GetState() == GameState::PLAY && !App::GetGameManager().GetIsPauseUI())
	{
		float index = (float)App::GetGameManager().MutateWorld().m_player.GetSelectedIndex();
		if (yoffset > 0)
		{
			index -= 1;
			if (index < 0)
			{
				index = 8;
			}
			App::GetGameManager().MutateWorld().m_player.SetSelectedIndex((unsigned int)index);
		}
		else if (yoffset < 0)
		{
			index += 1;
			if (index >= 9)
			{
				index = 0;
			}
			App::GetGameManager().MutateWorld().m_player.SetSelectedIndex((unsigned int)index);
		}
	}
}
