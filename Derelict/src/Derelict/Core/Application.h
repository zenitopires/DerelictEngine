#pragma once

#include "Window.h"
#include "Input.h"
#include "../Renderer/Buffer.h"
#include "../Renderer/Shader.h"
#include "../Events/ApplicationEvent.h"
#include "../Events/KeyEvent.h"

#include <memory>

namespace Derelict {
	class Application
	{
	public:
		Application();
		~Application();

		void Run();
		void OnEvent(Event& event);
		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

	private:
		bool m_Running = true;
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnKeyPressed(KeyPressedEvent& e);
		bool OnKeyReleased(KeyReleasedEvent& e);

		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Window> m_Window;
		std::unique_ptr<Input> m_Input;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		static Application* s_Instance;
	};

	Application* CreateApplication();
}