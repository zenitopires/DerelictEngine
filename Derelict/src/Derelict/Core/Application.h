#pragma once

#include "Window.h"
#include "Input.h"
#include "LayerStack.h"
#include "Timer.h"
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
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnKeyPressed(KeyPressedEvent& e);
		bool OnKeyReleased(KeyReleasedEvent& e);

	private:
		bool m_Running = true;
		std::unique_ptr<Derelict::Window> m_Window;
		std::unique_ptr<Derelict::Input> m_Input;
		std::unique_ptr<Derelict::Timer> m_Timer;
		LayerStack m_LayerStack;
		uint64_t m_LastFrameTime = 0;

		static Application* s_Instance;

	};

	Application* CreateApplication();
}