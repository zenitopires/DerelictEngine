#include "Derelict/src/Derelict/Core/Application.h"

#include <glad/glad.h>
#include <SDL3/SDL.h>

#include <memory>

#include <glm/gtc/matrix_transform.hpp>

class TestLayer : public Derelict::Layer
{
public:
	TestLayer() : Layer("Test Bed") ,
		m_Camera(-1.6f, 1.6f, -0.9f, 0.9f),
		m_TrianglePosition(0.0f)
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


		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f, 0.5f,  0.0f,
			-0.5f, 0.5f,  0.0f,
		};

		uint32_t squareIndices[6] = {
			0,1,2,
			2,3,0
		};

		m_SquareVertexArray = std::shared_ptr<Derelict::VertexArray>(Derelict::VertexArray::Create());
		m_SquareBuffer = std::shared_ptr<Derelict::VertexBuffer>(Derelict::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		m_SquareIndexBuffer = std::shared_ptr<Derelict::IndexBuffer>(Derelict::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));

		Derelict::AttributeLayout layout = {
			{ Derelict::ShaderDataType::Float3 }
		};

		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		Derelict::AttributeLayout squareLayout = {
			{ Derelict::ShaderDataType::Float3 }
		};
		m_SquareBuffer->SetLayout(squareLayout);
		m_SquareVertexArray->AddVertexBuffer(m_SquareBuffer);
		m_SquareVertexArray->SetIndexBuffer(m_SquareIndexBuffer);

		std::string vertexSource = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			out vec3 v_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			void main()
			{
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
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

		std::string blueShaderVertexSource = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			out vec3 v_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			void main()
			{
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
				v_Color = vec3(gl_Position);
			}
		)";

		std::string blueShaderFragmentSource = R"(
			#version 330 core

			out vec4 color;
			in vec3 v_Color;

			void main()
			{
				color = vec4(0.0, 1.0, 0.0, 1.0f);
			}
		)";

		m_Shader = std::shared_ptr<Derelict::Shader>(Derelict::Shader::Create(vertexSource, fragmentSource));
		m_BlueShader = std::shared_ptr<Derelict::Shader>(Derelict::Shader::Create(blueShaderVertexSource, blueShaderFragmentSource));

	}

	void OnUpdate(float deltaTime) override
	{
		Derelict::RenderCommand::SetClearColor({ 0.15f, 0.15f, 0.15f, 1.0f });
		Derelict::RenderCommand::Clear();

		if (Derelict::Input::IsKeyPressed(SDL_SCANCODE_A))
		{
			m_CameraPosition.x -= 1.0f * deltaTime;
		}
		else if (Derelict::Input::IsKeyPressed(SDL_SCANCODE_D))
		{
			m_CameraPosition.x += 1.0f * deltaTime;
		}
		if (Derelict::Input::IsKeyPressed(SDL_SCANCODE_S))
		{
			m_CameraPosition.y -= 1.0f * deltaTime;
		}
		else if (Derelict::Input::IsKeyPressed(SDL_SCANCODE_W))
		{
			m_CameraPosition.y += 1.0f * deltaTime;
		}


		if (Derelict::Input::IsKeyPressed(SDL_SCANCODE_J))
		{
			m_TrianglePosition.x -= 1.0f * deltaTime;
		}
		else if (Derelict::Input::IsKeyPressed(SDL_SCANCODE_L))
		{
			m_TrianglePosition.x += 1.0f * deltaTime;
		}
		if (Derelict::Input::IsKeyPressed(SDL_SCANCODE_I))
		{
			m_TrianglePosition.y += 1.0f * deltaTime;
		}
		else if (Derelict::Input::IsKeyPressed(SDL_SCANCODE_K))
		{
			m_TrianglePosition.y -= 1.0f * deltaTime;
		}

		Derelict::Renderer::BeginScene(m_Camera);
		{
			m_Camera.SetPosition(m_CameraPosition);
			m_Camera.SetRotation(m_CameraRotation);
			glm::mat4 test = glm::translate(glm::mat4(1.0f), m_TrianglePosition);
			for (int i = 0; i < 5; i++)
			{
				glm::mat4 test = glm::translate(glm::mat4(1.0f), glm::vec3((float)i, 0.0f, 0.0f));
				Derelict::Renderer::Submit(m_BlueShader, m_SquareVertexArray, test);
			}
			
			Derelict::Renderer::Submit(m_Shader, m_VertexArray, test);
		}
		Derelict::Renderer::EndScene();

	}

	void OnEvent(Derelict::Event& event) override
	{

	}

private:
	std::shared_ptr<Derelict::Shader> m_Shader;
	std::shared_ptr<Derelict::Shader> m_BlueShader;

	std::shared_ptr<Derelict::VertexArray> m_VertexArray;
	std::shared_ptr<Derelict::VertexBuffer> m_VertexBuffer;
	std::shared_ptr<Derelict::IndexBuffer> m_IndexBuffer;

	std::shared_ptr<Derelict::VertexArray> m_SquareVertexArray;
	std::shared_ptr<Derelict::VertexBuffer> m_SquareBuffer;
	std::shared_ptr<Derelict::IndexBuffer> m_SquareIndexBuffer;

	Derelict::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraRotation;

	glm::vec3 m_TrianglePosition;
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