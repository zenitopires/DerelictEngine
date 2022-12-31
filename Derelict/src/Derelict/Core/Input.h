#pragma once

namespace Derelict {
	class Input {
	public:
		inline static bool KeyPressed(int keycode) { s_Instance->KeyPressedImpl(keycode); }
		inline static bool MouseButtonPressed(int button) { s_Instance->MouseButtonPressed(button); }
		inline static bool GetMouseX() { s_Instance->GetMouseXImpl(); }
		inline static bool GetMouseY() { s_Instance->GetMouseYImpl(); }
	protected:
		virtual bool KeyPressedImpl(int keycode) = 0;
		virtual bool MouseButtonPressedImpl(int button) = 0;
		virtual bool GetMouseXImpl() = 0;
		virtual bool GetMouseYImpl() = 0;
	private:
		static Input* s_Instance;
	};
}