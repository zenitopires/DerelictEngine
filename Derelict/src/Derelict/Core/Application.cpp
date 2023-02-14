#include <glad/glad.h>
#include "Application.h"
#include "Core.h"

#include <SDL3/SDL.h>

namespace Derelict {
#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		if (s_Instance) 
		{
			std::cout << "Instance of application already exists.\n";
			exit(-1);
		}

		s_Instance = this;
		WindowProps props("Derelict Engine", 1280, 720, true);
		m_Window = Scope<Window>(Window::Create(props));
		m_Input = Scope<Input>(Input::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
		m_Timer = Scope<Timer>(Timer::Create());
		m_Timer->Start();

		Renderer::Init();
		RenderCommand::Init();
	}

	Application::~Application()
	{

	}


	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		std::cout << "Closing window.";
		m_Running = false;
		return true;
	}

	bool Application::OnKeyPressed(KeyPressedEvent& e)
	{
		return true;
	}

	bool Application::OnKeyReleased(KeyReleasedEvent& e)
	{
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		RenderCommand::SetViewport(e.GetWidth(), e.GetHeight());
		return true;
	}

	void Application::OnEvent(Event& event)
	{
		//std::cout << event.ToString() << '\n';

		EventDispatcher dispatcher(event);

		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(Application::OnKeyPressed));
		dispatcher.Dispatch<KeyReleasedEvent>(BIND_EVENT_FN(Application::OnKeyReleased));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize));


		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); ) 
		{
			(*--it)->OnEvent(event);
			if (event.Handled)
				break;
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::Run()
	{
		while (m_Running)
		{
			m_Timer->Tick();

			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate(m_Timer->DeltaTime());
			}

			//m_Input->OnUpdate();
			m_Window->OnUpdate();
		}
		m_Timer->Stop();
	}
	//Derelict::Application* Application::s_Instance;

}