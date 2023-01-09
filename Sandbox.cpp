#include "Derelict/src/Derelict/Core/Application.h"

#include <glad/glad.h>
#include <SDL3/SDL.h>

#include <memory>

class TestLayer : public Derelict::Layer
{
public:
	TestLayer() : Layer("Test Bed") ,
		m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
	{
		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f,  0.0f,
		};

		uint32_t indices[3] = {
			0,1,2
		};

		m_VertexArray = std::shared_ptr<Derelict::VertexArray>(Derelict::VertexArray::Create());
		m_VertexBuffer = std::shared_ptr<Derelict::VertexBuffer>(Derelict::VertexBuffer::Create(vertices, sizeof(vertices)));
		m_IndexBuffer = std::shared_ptr<Derelict::IndexBuffer>(Derelict::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		Derelict::AttributeLayout layout = {
			{ Derelict::ShaderDataType::Float3 }
		};

		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		std::string vertexSource = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			out vec3 v_Color;

			uniform mat4 u_ViewProjection;

			void main()
			{
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
				v_Color = vec3(gl_Position);
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

		m_Shader = std::unique_ptr<Derelict::Shader>(Derelict::Shader::Create(vertexSource, fragmentSource));
	}

	void OnUpdate(float deltaTime) override
	{
		//std::cout << "Delta time: " << timestep.GetSeconds() << "s " << timestep.GetMilliseconds() << "ms" << '\n';

		//glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
		//glClear(GL_COLOR_BUFFER_BIT);

		Derelict::RenderCommand::SetClearColor({ 0.15f, 0.15f, 0.15f, 1.0f });
		Derelict::RenderCommand::Clear();

		// RenderCommand::SetClearColor()
		// RenderCommand::Clear()

		if (Derelict::Input::IsKeyPressed(SDL_SCANCODE_A))
		{
			m_CameraPosition.x += 1.0f * deltaTime;
		}
		else if (Derelict::Input::IsKeyPressed(SDL_SCANCODE_D))
		{
			m_CameraPosition.x -= 1.0f * deltaTime;
		}
		if (Derelict::Input::IsKeyPressed(SDL_SCANCODE_S))
		{
			m_CameraPosition.y += 1.0f * deltaTime;
		}
		else if (Derelict::Input::IsKeyPressed(SDL_SCANCODE_W))
		{
			m_CameraPosition.y -= 1.0f * deltaTime;
		}

		Derelict::Renderer::BeginScene();
		{
			m_Camera.SetPosition(m_CameraPosition);
			m_Camera.SetRotation(m_CameraRotation);

			m_Shader->Bind();
			m_Shader->UploadMat4("u_ViewProjection", m_Camera.GetViewProjectionMatrix());
			Derelict::Renderer::Submit(m_VertexArray);
			//glDrawArrays(GL_TRIANGLES, 0, 3);
		}
		Derelict::Renderer::EndScene();

	}

	void OnEvent(Derelict::Event& event) override
	{

	}

private:
	std::unique_ptr<Derelict::Shader> m_Shader;
	std::shared_ptr<Derelict::IndexBuffer> m_IndexBuffer;
	std::shared_ptr<Derelict::VertexBuffer> m_VertexBuffer;
	std::shared_ptr<Derelict::VertexArray> m_VertexArray;

	Derelict::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraRotation;
};

class Sandbox : public Derelict::Application
{
public:
	Sandbox()
	{
		PushLayer(new TestLayer());
	}
	~Sandbox() {}

private:
};

Derelict::Application* Derelict::CreateApplication()
{
	return new Sandbox();
}