#pragma once

#include "Window.h"

#include <memory>

namespace Derelict {
	class Application
	{
	public:
		Application();
		~Application();

		void Run();
		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

	private:
		bool m_Running = true;
		std::unique_ptr<Window> m_Window;
		static Application* s_Instance;
	};

	Application* CreateApplication();
}