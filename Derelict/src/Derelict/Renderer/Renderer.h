#pragma once

#include "../Core/Core.h"
#include "RendererAPI.h"
#include "RenderCommand.h"
#include "Shader.h"
#include "OrthographicCamera.h"

namespace Derelict {
	class Renderer
	{
	public:
		static void BeginScene(OrthographicCamera& camera); // TODO: Take scene parameters e.g. camera, environment, etc.
		static void EndScene();

		static void Submit(
			const Ref<Shader>& shader,
			const Ref<VertexArray>& vertexArray,
			const glm::mat4 transform = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};
}

