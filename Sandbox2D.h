#pragma once
#include "Derelict/src/Derelict/Core/Core.h"
#include "Derelict/src/Derelict/Core/Application.h"
#include "Derelict/src/Derelict/Platform/OpenGL/OpenGLShader.h"
#include "Derelict/src/Derelict/Platform/OpenGL/OpenGLTexture2D.h"
#include "Derelict/src/Derelict/Core/OrthographicCameraController.h"


class Sandbox2D : public Derelict::Layer
{
public:
	Sandbox2D();
	~Sandbox2D();
	void OnUpdate(float deltaTime) override;
	void OnEvent(Derelict::Event& event) override;
	void OnAttach() override;
	void OnDetach() override;

private:
	Derelict::ShaderLibrary m_ShaderLibrary;

	Derelict::Ref<Derelict::Shader> m_Shader;
	Derelict::Ref<Derelict::Shader> m_FlatColorShader;

	Derelict::Ref<Derelict::VertexArray> m_VertexArray;
	Derelict::Ref<Derelict::VertexBuffer> m_VertexBuffer;
	Derelict::Ref<Derelict::IndexBuffer> m_IndexBuffer;

	Derelict::Ref<Derelict::VertexArray> m_SquareVertexArray;
	Derelict::Ref<Derelict::VertexBuffer> m_SquareBuffer;
	Derelict::Ref<Derelict::IndexBuffer> m_SquareIndexBuffer;

	Derelict::Ref<Derelict::Texture2D> m_Texture;

	Derelict::OrthographicCameraController m_CameraController;
	glm::vec3 m_CameraPosition;
	float m_CameraRotation;

	glm::vec3 m_TrianglePosition;

};

