#include "InputSystems.h"
#include <SDL.h>
#include <iostream>

namespace neu 
{

	const uint32_t key_space = SDL_SCANCODE_SPACE;
	const uint32_t key_up = SDL_SCANCODE_UP;
	const uint32_t key_down = SDL_SCANCODE_DOWN;
	const uint32_t key_left = SDL_SCANCODE_LEFT;
	const uint32_t key_right = SDL_SCANCODE_RIGHT;
	const uint32_t key_escape = SDL_SCANCODE_ESCAPE;
	const uint32_t key_q = SDL_SCANCODE_Q;
	const uint32_t key_e = SDL_SCANCODE_E;

	const uint32_t button_left = 0;
	const uint32_t button_middle = 1;
	const uint32_t button_right = 2;


	void neu::InputSystem::Initialize()
	{
		const uint8_t* keyboardState = SDL_GetKeyboardState(&m_numKeys);
		
		m_keyboardState.resize(m_numKeys);
		
		std::copy(keyboardState, keyboardState + m_numKeys, m_keyboardState.begin());
		
		m_prevKeyboardState = m_keyboardState;
	}
	
	void neu::InputSystem::Shutdown()
	{
	
	}
	
	void neu::InputSystem::Update()
	{
		SDL_Event event;
		SDL_PollEvent(&event);
		//save previous keyboard state
		m_prevKeyboardState = m_keyboardState;
		
		//get current keyboard state
		const uint8_t* keyboardState = SDL_GetKeyboardState(nullptr);
		std::copy(keyboardState, keyboardState + m_numKeys, m_keyboardState.begin());
		
		//std::cout << (bool)m_keyboardState[SDL_SCANCODE_SPACE] << std::endl
		//for (int i = 0; i < 120; i++)
		//{
		//	std::cout << (bool)m_keyboardState[i];
		//}
		//std::cout << std::endl;
		
		m_prevMouseButtonState = m_mouseButtonState;
		int x, y;
		uint32_t buttons = SDL_GetMouseState(&x, &y);
		m_mousePosition = neu::Vector2{ x, y };
		m_mouseButtonState[0] = buttons & SDL_BUTTON_LMASK; //buttons [0001] & [ORML]
		m_mouseButtonState[1] = buttons & SDL_BUTTON_MMASK; //buttons [0010] & [ORML]
		m_mouseButtonState[2] = buttons & SDL_BUTTON_RMASK; //buttons [0100] & [ORML]
	}

	InputSystem::State InputSystem::GetKeyState(uint32_t key)
	{
		State state = State::Idle;

		bool keyDown = GetKeyDown(key);
		bool prevKeyDown = GetPreviousKeyDown(key);

		if (keyDown == 1 && prevKeyDown == 1)
		{
			state = State::Held;
		}

		if (keyDown == 0 && prevKeyDown == 0)
		{
			state = State::Idle;
		}

		if (keyDown == 0 && prevKeyDown == 1)
		{
			state = State::Released;
		}

		if (keyDown == 1 && prevKeyDown == 0)
		{
			state = State::Pressed;
		}
		
		return state;
	}

	InputSystem::State InputSystem::GetButtonState(uint32_t button)
	{
		State state = State::Idle;
		
		bool buttonDown = GetButtonDown(button);
		bool prevButtonDown = GetPreviousButtonDown(button);
		
		if (buttonDown == 1 && prevButtonDown == 1)
		{
			state = State::Held;
		}
		
		if (buttonDown == 0 && prevButtonDown == 0)
		{
			state = State::Idle;
		}
		
		if (buttonDown == 0 && prevButtonDown == 1)
		{
			state = State::Released;
		}
		
		if (buttonDown == 1 && prevButtonDown == 0)
		{
			state = State::Pressed;
		}
		
		return state;
	}
}