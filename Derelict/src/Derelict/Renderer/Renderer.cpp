#include "Renderer.h"


// Renderer is in charge of abstraction such as bind vertex array, bind the shaders,
// set up the materials, do all the sorting, etc...

namespace Derelict {

	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, 
		const std::shared_ptr<VertexArray>& vertexArray,
		const glm::mat4 transform)
	{
		shader->Bind();
		shader->UploadMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		shader->UploadMat4("u_Transform", transform);

		vertexArray->Bind(); 
		RenderCommand::DrawIndexed(vertexArray);
	}

}