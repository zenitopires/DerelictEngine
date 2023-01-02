#include <glad/glad.h>
#include "Application.h"

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

	void Application::Run()
	{
		unsigned int vao;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f,  0.0f,
		};

		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		std::string vertexSource = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			out vec3 v_Color;

			void main()
			{
				gl_Position = vec4(a_Position, 1.0);
				v_Color = a_Position;
			}
		)";

		std::string fragmentSource = R"(
			#version 330 core

			out vec4 color;
			in vec3 v_Color;

			void main()
			{
				color = vec4(v_Color.r + 0.5, v_Color.g + 0.5, v_Color.b + 0.5, 1.0f);
			}
		)";

		m_Shader.reset(Shader::Create(vertexSource, fragmentSource));

		while (m_Running)
		{

			glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Shader->Bind();
			glBindVertexArray(vao);
			glDrawArrays(GL_TRIANGLES, 0, 3);

			m_Input->OnUpdate();
			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		std::cout << "Closing window.";
		m_Running = false;
		return true;
	}

	bool Application::OnKeyPressed(KeyPressedEvent& e)
	{
		std::cout << "Key Pressed: " << (char)e.GetKeyCode() << '\n';
		return true;
	}

	bool Application::OnKeyReleased(KeyReleasedEvent& e)
	{
		std::cout << "Key Released: " << (char)e.GetKeyCode() << '\n';
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

	//Derelict::Application* Application::s_Instance;

}