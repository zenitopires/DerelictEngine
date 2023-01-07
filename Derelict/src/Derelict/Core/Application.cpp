#include <glad/glad.h>
#include "Application.h"
#include "../Platform/OpenGL/OpenGLBuffer.h"

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
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Input = std::unique_ptr<Input>(Input::Create());
		m_Input->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
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
		std::cout << "Key Pressed: " << e.GetKeyCode() << '\n';
		return true;
	}

	bool Application::OnKeyReleased(KeyReleasedEvent& e)
	{
		//std::cout << "Key Released: " << (char)e.GetKeyCode() << '\n';
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
			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate();
			}

			m_Input->OnUpdate();
			m_Window->OnUpdate();
		}
	}
	//Derelict::Application* Application::s_Instance;

}