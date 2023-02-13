#include "SDLInputHandler.h"
#include "../../Core/Application.h"
#include "../../Events/ApplicationEvent.h"
#include "../../Events/KeyEvent.h"
#include "../../Events/MouseEvent.h"


#include <SDL3/SDL.h>

#include <iostream>

namespace Derelict {
	Input* Input::s_Instance = new SDLInputHandler();

	Input* Input::Create() { return new SDLInputHandler(); }


	static void CheckKeyStates()
	{
		 const Uint8* keys = SDL_GetKeyboardState(NULL);
		 SDL_PumpEvents();
	}

	SDLInputHandler::SDLInputHandler()
	{
	}

	void SDLInputHandler::OnUpdate()
	{
		while (SDL_PollEvent(&m_Data.Event))
		{
			switch (m_Data.Event.type)
			{
			case SDL_EVENT_QUIT:
			{
				WindowCloseEvent event;
				m_Data.callback(event);
				break;
			}
			case SDL_EVENT_KEY_DOWN:
			{
				KeyPressedEvent event(m_Data.Event.key.keysym.sym, 0);
				m_Data.callback(event);
				break;
			}
			case SDL_EVENT_KEY_UP:
			{
				KeyReleasedEvent event(m_Data.Event.key.keysym.sym);
				m_Data.callback(event);
			}
			case SDL_EVENT_MOUSE_WHEEL:
			{
				std::cout << "Mouse scroll event\n";
				MouseScrollEvent event(m_Data.Event.wheel.x, m_Data.Event.wheel.y);
				m_Data.callback(event);
			}
			}
		}
	}

	bool SDLInputHandler::KeyPressedImpl(int scancode)
	{
		SDL_PumpEvents();
		const Uint8* keys = SDL_GetKeyboardState(NULL);

		if (keys[scancode] == 1)
			return true;
		return false;
	}

	bool SDLInputHandler::MouseButtonPressedImpl(int button)
	{
		SDL_PumpEvents();
		Uint8 buttons = SDL_GetMouseState(nullptr, nullptr);
		return (buttons & button) != 0;
	}

	bool SDLInputHandler::MouseScrollImpl()
	{

		return false;
	}

	bool SDLInputHandler::GetMouseXImpl()
	{
		return true;
	}

	bool SDLInputHandler::GetMouseYImpl()
	{
		return true;
	}
}