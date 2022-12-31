#pragma once

namespace Derelict {
	class Input {
	public:
		virtual bool KeyPressed(int keycode);
		virtual bool MouseButtonPressed(int button);
		virtual bool GetMouseX();
		virtual bool GetMouseY();
	};
}