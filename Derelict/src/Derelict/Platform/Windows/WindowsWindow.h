#pragma once

#include <SDL3/SDL.h>
#include "../../Core/Window.h"

namespace Derelict {
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }
		virtual void* GetNativeWindow() const { return m_Window; }

	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

	private:
		SDL_Window* m_Window;

		SDL_GLContext m_Context;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
		};

		WindowData m_Data;
	};
}

