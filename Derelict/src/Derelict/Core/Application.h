#pragma once

#include "Window.h"
#include "Input.h"
#include "LayerStack.h"
#include "../Renderer/Buffer.h"
#include "../Renderer/VertexArray.h"
#include "../Renderer/Shader.h"
#include "../Renderer/OrthographicCamera.h"
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

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

	private:
		bool m_Running = true;
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnKeyPressed(KeyPressedEvent& e);
		bool OnKeyReleased(KeyReleasedEvent& e);

		std::unique_ptr<Derelict::Window> m_Window;
		std::unique_ptr<Derelict::Input> m_Input;
		LayerStack m_LayerStack;

		static Application* s_Instance;

	};

	Application* CreateApplication();
}