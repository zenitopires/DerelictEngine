#include "Renderer.h"


// Renderer is in charge of abstraction such as bind vertex array, bind the shaders,
// set up the materials, do all the sorting, etc...

namespace Derelict {

	void Renderer::BeginScene()
	{

	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
	{
		vertexArray->Bind(); 
		RenderCommand::DrawIndexed(vertexArray);
	}

}