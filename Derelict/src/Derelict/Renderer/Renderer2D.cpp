#include "Renderer2D.h"

#include "../Core/Core.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Buffer.h"
#include "RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Derelict {

	struct Renderer2DStorage
	{
		Ref<VertexArray> squareVA;
		Ref<Shader> squareShader;
	};

	static Renderer2DStorage* s_Data;

	void Renderer2D::Init()
	{
		s_Data = new Renderer2DStorage;

		float vertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.5f, 0.5f,  0.0f,
			-0.5f, 0.5f, 0.0f
		};

		uint32_t indices[6] = {
			0,1,2,2,3,0
		};

		s_Data->squareVA = Derelict::VertexArray::Create();

		Ref<VertexBuffer> m_VertexBuffer;
		m_VertexBuffer = Derelict::VertexBuffer::Create(vertices, sizeof(vertices));

		Ref<Derelict::IndexBuffer> m_IndexBuffer;
		m_IndexBuffer = Derelict::Ref<Derelict::IndexBuffer>(Derelict::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		Derelict::AttributeLayout layout = {
			{ Derelict::ShaderDataType::Float3, "a_Position"},
		};

		m_VertexBuffer->SetLayout(layout);
		s_Data->squareVA->AddVertexBuffer(m_VertexBuffer);
		s_Data->squareVA->SetIndexBuffer(m_IndexBuffer);

		s_Data->squareShader = Derelict::Ref<Derelict::Shader>(Derelict::Shader::Create("assets/shaders/Square.glsl"));
	}

	void Renderer2D::Shutdown()
	{
		delete s_Data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		s_Data->squareShader->Bind();
		s_Data->squareShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	}

	void Renderer2D::EndScene()
	{

	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& scale, const glm::vec4& color /*= { 0.5f, 0.5f, 0.5f, 1.0f } */)
	{
		DrawQuad({ position.x, position.y, 0.0f }, scale, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& scale, const glm::vec4& color /*= { 0.5f, 0.5f, 0.5f, 1.0f }*/)
	{
		s_Data->squareShader->Bind();
		s_Data->squareShader->SetFloat4("u_Color", color);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { scale.x, scale.y, 0.0f });
		s_Data->squareShader->SetMat4("u_Transform", glm::mat4(1.0f) * transform);

		s_Data->squareVA->Bind();
		RenderCommand::DrawIndexed(s_Data->squareVA);
	}

}