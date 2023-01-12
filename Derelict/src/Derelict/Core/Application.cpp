#include <glad/glad.h>
#include "Application.h"


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
		m_Window = std::unique_ptr<Window>(Window::Create(props));
		m_Input = std::unique_ptr<Input>(Input::Create());
		m_Input->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
		m_Timer = std::unique_ptr<Timer>(Timer::Create());

		m_Timer->Start();
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

	void Application::OnEvent(Event& event)
	{
		//std::cout << event.ToString() << '\n';

		EventDispatcher dispatcher(event);

		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(Application::OnKeyPressed));
		dispatcher.Dispatch<KeyReleasedEvent>(BIND_EVENT_FN(Application::OnKeyReleased));
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

			std::cout << std::fixed;
			std::cout << m_Timer->DeltaTime() * 1000 << std::endl;

			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate(m_Timer->DeltaTime());
			}

			m_Input->OnUpdate();
			m_Window->OnUpdate();
		}
		m_Timer->Stop();
	}
	//Derelict::Application* Application::s_Instance;

}