#include "Renderer.h"

#include "../Core/Core.h"
#include "../Platform/OpenGL/OpenGLShader.h"
#include "Renderer2D.h"

// Renderer is in charge of abstraction such as bind vertex array, bind the shaders,
// set up the materials, do all the sorting, etc...

namespace Derelict {

	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::Init()
	{
		RenderCommand::Init();
		Renderer2D::Init();
	}

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const Ref<Shader>& shader, 
		const Ref<VertexArray>& vertexArray,
		const glm::mat4 transform)
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadMat4("u_Transform", transform);

		vertexArray->Bind(); 
		RenderCommand::DrawIndexed(vertexArray);
	}

}