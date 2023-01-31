#pragma once
#include "../Events/Event.h"

#include <iostream>
#include <functional>

namespace Derelict {
	class Input {
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		inline static bool IsKeyPressed(int keycode) { return s_Instance->KeyPressedImpl(keycode); }
		inline static bool IsMouseButtonPressed(int button) { return s_Instance->MouseButtonPressedImpl(button); }

		static Input* Create();
		virtual void OnUpdate() = 0;
		virtual bool KeyPressedImpl(int keycode) = 0;
		virtual bool MouseButtonPressedImpl(int button) = 0;
		virtual bool MouseScrollImpl() = 0;
		virtual bool GetMouseXImpl() = 0;
		virtual bool GetMouseYImpl() = 0;
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;

	private:
		static Input* s_Instance;
	};
}