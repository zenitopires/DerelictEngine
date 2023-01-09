#pragma once

#include "RendererAPI.h"
#include "RenderCommand.h"

namespace Derelict {
	class Renderer
	{
	public:
		static void BeginScene(); // TODO: Take scene parameters e.g. camera, environment, etc.
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};
}

