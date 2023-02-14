#pragma once

#include "RendererAPI.h"
#include "../Core/Core.h"


namespace Derelict {
	class RenderCommand
	{
	public:
		inline static void Init() { s_RendererAPI->Init(); }
		inline static void Clear() { s_RendererAPI->Clear(); }
		inline static void SetClearColor(const glm::vec4& color) { 
			s_RendererAPI->SetClearColor(color);
		}
		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray)
		{
			s_RendererAPI->DrawIndexed(vertexArray);
		}
		inline static void SetViewport(float width, float height) { s_RendererAPI->SetViewport(width, height); }
	private:
		static RendererAPI* s_RendererAPI;
	};
}

