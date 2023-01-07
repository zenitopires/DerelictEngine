#include "SDLInputHandler.h"
#include "../../Core/Application.h"
#include "../../Events/ApplicationEvent.h"
#include "../../Events/KeyEvent.h"


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
			case SDL_QUIT:
			{
				WindowCloseEvent event;
				m_Data.callback(event);
				break;
			}
			case SDL_KEYDOWN:
			{
				KeyPressedEvent event(m_Data.Event.key.keysym.sym, 0);
				m_Data.callback(event);
				break;
			}
			case SDL_KEYUP:
				KeyReleasedEvent event(m_Data.Event.key.keysym.sym);
				m_Data.callback(event);
			}
		}
	}

	bool SDLInputHandler::KeyPressedImpl(int scancode)
	{
		const Uint8* keys = SDL_GetKeyboardState(NULL);
		SDL_PumpEvents();

		if (keys[scancode] == 1)
			return true;
		return false;
	}

	bool SDLInputHandler::MouseButtonPressedImpl(int button)
	{
		return true;
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