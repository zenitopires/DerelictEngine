#include "Sandbox2D.h"

#include "Derelict/src/Derelict/Renderer/Renderer2D.h"

Sandbox2D::Sandbox2D() : Layer("Sandbox2D Layer"),
	m_CameraController(1280.0f / 720.0f),
	m_TrianglePosition(0.0f)
{

}

Sandbox2D::~Sandbox2D()
{

}

void Sandbox2D::OnUpdate(float deltaTime)
{
		m_CameraController.OnUpdate(deltaTime);

		Derelict::RenderCommand::SetClearColor({ 0.15f, 0.15f, 0.15f, 1.0f });
		Derelict::RenderCommand::Clear();

		std::vector<bool> grid = {
			false, false, true,
			false, false, true,
			true, true, true
		};

		//glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
		Derelict::Renderer2D::BeginScene(m_CameraController.GetCamera());
		{
			//glm::vec3 pos(0.0f, 0.0f, 0.0f);
			//glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
			//Derelict::Renderer::Submit(m_Shader, m_VertexArray, transform);
			Derelict::Renderer2D::DrawQuad({ 0.0f, 0.2f }, { 1.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f });
			Derelict::Renderer2D::DrawQuad({ 0.0f, -1.2f }, { 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f });
			Derelict::Renderer2D::DrawQuad({ -0.7f, -0.5f }, { 1.0f, 1.0f }, { 1.0f, 1.0f, 0.0f, 1.0f });
			Derelict::Renderer2D::DrawQuad({ 0.7f, -0.5f }, { 1.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f });


			//int index = 0;
			//for (auto b : grid)
			//{
			//	if (b == true)
			//		Derelict::Renderer2D::DrawQuad({ index * 0.3f, index * 0.2f }, { 0.5f, 0.5f });
			//	index++;
			//}

		}
		Derelict::Renderer2D::EndScene();
}


void Sandbox2D::OnEvent(Derelict::Event& event)
{
	m_CameraController.OnEvent(event);
}

void Sandbox2D::OnAttach()
{
}

void Sandbox2D::OnDetach()
{

}
