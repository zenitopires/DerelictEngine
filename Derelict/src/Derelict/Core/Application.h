#pragma once

#include "Core.h"
#include "Window.h"
#include "Input.h"
#include "LayerStack.h"
#include "Timer.h"
#include "../Renderer/Buffer.h"
#include "../Renderer/VertexArray.h"
#include "../Renderer/Shader.h"
#include "../Renderer/Renderer.h"
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
		bool OnWindowResize(WindowResizeEvent& e);

	protected:
		Scope<Derelict::Window> m_Window;
	private:
		bool m_Running = true;
		Scope<Derelict::Input> m_Input;
		Scope<Derelict::Timer> m_Timer;
		LayerStack m_LayerStack;
		uint64_t m_LastFrameTime = 0;

		static Application* s_Instance;

	};

	Application* CreateApplication();
}