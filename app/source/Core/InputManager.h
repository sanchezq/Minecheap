#pragma once
#include <unordered_map>
#include "GLFW/glfw3.h"

class InputManager
{
public:
	InputManager();
	~InputManager() = default;

	enum class KeyAction
	{
		MOVE_CAMERA_FORWARD,
		MOVE_CAMERA_LEFT,
		MOVE_CAMERA_RIGHT,
		MOVE_CAMERA_BACKWARD,

		MOVE_PLAYER_FORWARD,
		MOVE_PLAYER_LEFT,
		MOVE_PLAYER_RIGHT,
		MOVE_PLAYER_BACKWARD,
		PLAYER_JUMP,
		PLAYER_BREAK_BLOC,
		PLAYER_PLACE_BLOC,

		INVENTORY,

		NOKEY //kepp this entry last
	};

	void  InitializeWindowCallBack(GLFWwindow* window);

	void ProcessInput(GLFWwindow* window, float delta);

	void SetKeyChange(KeyAction key);
	KeyAction GetKeyChange() const;
	void ChangeInput(KeyAction action, int key);

	bool m_ChangeKey = false;
	std::unordered_map<KeyAction, int> GetMap() const;
private:
	std::unordered_map<KeyAction, int> m_settings;
	KeyAction m_keyChange = KeyAction::NOKEY;

};

//class InputCommand
//{
//public:
//	virtual void operator()() = 0;
//};

//struct InputCommandDesc
//{
//	InputCommandDesc(const sf::Event& event, InputCommand* input)
//	{
//		myEvent = event;
//		m_command = input;
//	}
//	sf::Event myEvent;
//
//	InputCommand* m_command;
//};
//
//class InputCommandMap
//{
//public:
//	InputCommandMap() = default;
//	~InputCommandMap()
//	{
//		for (void* commandPtr : m_callbackPtr)
//		{
//			delete commandPtr;
//		}
//	}
//
//	using InputMappper = std::unordered_map<sf::Event::EventType, std::vector < InputCommandDesc >>;
//
//
//	void AddCommandDescriptor(const InputCommandDesc& desc);
//
//	void registerCallback(void* callback)
//	{
//		m_callbackPtr.push_back(callback);
//	}
//
//	InputCommand* GetInputCommand(const sf::Event& event);
//
//private:
//	InputMappper m_inputMap;
//	std::vector<void*> m_callbackPtr;
//};
//
//class InputService : public Manager
//{
//public:
//
//	InputService() = delete;
//	InputService(GameManager* game);
//	~InputService() = default;
//
//	void SetInputMap(InputCommandMap* inputMap) { m_map = inputMap; }
//
//	bool UpdateInputs();
//
//private:
//	InputCommandMap* m_map = nullptr;
//};
//
//
//template<typename MethodOwner, typename Return, typename... Args>
//class CallbackCommand : public InputCommand
//{
//public:
//
//	typedef Return(MethodOwner::* MethodPtr)(Args...);
//
//	void operator()() override
//	{
//		m_callback();
//	}
//
//	CallbackCommand(InputCommandMap& inputMap, MethodPtr method, MethodOwner* owner, Args... args) :
//		m_callback(std::bind(method, owner, args...))
//	{
//		inputMap.registerCallback(this);
//		//register need to avoid double deleting callback when command is linked to more than one key
//	}
//
//	~CallbackCommand() = default;
//
//private:
//	std::function<Return()> m_callback;
//
//};
//
//template<typename T, typename R, typename... Args> //helper to deduce the types.
//CallbackCommand<T, R, Args...>MakeCallback(R(T::* pmf)(Args...), T* p, Args... data)
//{
//	return CallbackCommand<T, R, Args...>(pmf, p, data);
//}