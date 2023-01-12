#include "Derelict/src/Derelict/Core/Core.h"
#include "Derelict/src/Derelict/Core/Application.h"
#include "Derelict/src/Derelict/Platform/OpenGL/OpenGLShader.h"

#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <glm/gtc/matrix_transform.hpp>

#include <memory>


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

		m_VertexArray = Derelict::Ref<Derelict::VertexArray>(Derelict::VertexArray::Create());
		m_VertexBuffer = Derelict::Ref<Derelict::VertexBuffer>(Derelict::VertexBuffer::Create(vertices, sizeof(vertices)));
		m_IndexBuffer = Derelict::Ref<Derelict::IndexBuffer>(Derelict::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));


		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
		};

		uint32_t squareIndices[6] = {
			0,1,2,
			2,3,0
		};

		m_SquareVertexArray = Derelict::Ref<Derelict::VertexArray>(Derelict::VertexArray::Create());
		m_SquareBuffer = Derelict::Ref<Derelict::VertexBuffer>(Derelict::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		m_SquareIndexBuffer = Derelict::Ref<Derelict::IndexBuffer>(Derelict::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));

		Derelict::AttributeLayout layout = {
			{ Derelict::ShaderDataType::Float3, "a_Position"},
		};

		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		Derelict::AttributeLayout squareLayout = {
			{ Derelict::ShaderDataType::Float3, "a_Position"},
			{ Derelict::ShaderDataType::Float2, "a_TexCoord"}
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


		m_Shader = Derelict::Ref<Derelict::Shader>(Derelict::Shader::Create(vertexSource, fragmentSource));

		std::string flatColorShaderVertexSource = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			out vec3 v_Color;
			uniform vec4 u_Red;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			void main()
			{
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
				v_Color = vec3(gl_Position);
			}
		)";

		std::string flatColorShaderFragmentSource = R"(
			#version 330 core

			out vec4 color;
			in vec3 v_Color;

			uniform vec4 u_Color;

			void main()
			{
				//color = vec4(0.0, 1.0, 0.0, 1.0f);
				color = u_Color;
			}
		)";

		m_FlatColorShader = Derelict::Ref<Derelict::Shader>(Derelict::Shader::Create(flatColorShaderVertexSource, flatColorShaderFragmentSource));

		std::string texureShaderVertexSource = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;
			out vec3 v_Color;
			out vec2 v_TexCoord;			

			uniform vec4 u_Red;
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			void main()
			{
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
				v_Color = vec3(gl_Position);
				v_TexCoord = a_TexCoord;
			}
		)";

		std::string texureShaderFragmentSource = R"(
			#version 330 core

			out vec4 color;
			in vec3 v_Color;
			in vec2 v_TexCoord;

			uniform vec4 u_Color;

			void main()
			{
				//color = vec4(0.0, 1.0, 0.0, 1.0f);
				//color = u_Color;
				color = vec4(v_TexCoord, 0.0, 1.0);
			}
		)";

		m_TextureShader = Derelict::Ref<Derelict::Shader>(Derelict::Shader::Create(texureShaderVertexSource, texureShaderFragmentSource));

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

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
		Derelict::Renderer::BeginScene(m_Camera);
		{
			m_Camera.SetPosition(m_CameraPosition);
			m_Camera.SetRotation(m_CameraRotation);
			glm::mat4 test = glm::translate(glm::mat4(1.0f), m_TrianglePosition);
			glm::vec4 redColor(0.8f, 0.2f, 0.3f, 1.0f);
			glm::vec4 blueColor(0.2f, 0.3f, 0.8f, 1.0f);
			
			std::dynamic_pointer_cast<Derelict::OpenGLShader>(m_FlatColorShader)->Bind();

			for (int y = 0; y < 20; y++)
			{
				for (int x = 0; x < 20; x++)
				{
					glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
					glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
					if (x % 2 == 0)
						std::dynamic_pointer_cast<Derelict::OpenGLShader>(m_FlatColorShader)->UploadFloat4("u_Color", redColor);
					else
						std::dynamic_pointer_cast<Derelict::OpenGLShader>(m_FlatColorShader)->UploadFloat4("u_Color", blueColor);
					Derelict::Renderer::Submit(m_FlatColorShader, m_SquareVertexArray, transform);
				}
			}

			Derelict::Renderer::Submit(m_TextureShader, m_SquareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

			//Derelict::Renderer::Submit(m_Shader, m_VertexArray, test);
		}
		Derelict::Renderer::EndScene();

	}

	void OnEvent(Derelict::Event& event) override
	{

	}

private:
	Derelict::Ref<Derelict::Shader> m_Shader;
	Derelict::Ref<Derelict::Shader> m_FlatColorShader, m_TextureShader;

	Derelict::Ref<Derelict::VertexArray> m_VertexArray;
	Derelict::Ref<Derelict::VertexBuffer> m_VertexBuffer;
	Derelict::Ref<Derelict::IndexBuffer> m_IndexBuffer;

	Derelict::Ref<Derelict::VertexArray> m_SquareVertexArray;
	Derelict::Ref<Derelict::VertexBuffer> m_SquareBuffer;
	Derelict::Ref<Derelict::IndexBuffer> m_SquareIndexBuffer;

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