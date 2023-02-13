#pragma once

#include "../../Core/Input.h"
#include <SDL3/SDL.h>

namespace Derelict {
	struct Scancode {
		bool hasScancode = false;
		SDL_Scancode code;
	};

	class SDLInputHandler : public Input
	{
	public:
		SDLInputHandler();


		virtual bool KeyPressedImpl(int keycode) override;
		virtual bool MouseButtonPressedImpl(int button) override;
		virtual bool MouseScrollImpl() override;
		virtual bool GetMouseXImpl() override;
		virtual bool GetMouseYImpl() override;

	};
}

