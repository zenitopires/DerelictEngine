#pragma once

#include "OrthographicCamera.h"
#include "Texture.h"

#include <glm/glm.hpp>

namespace Derelict {
	class Renderer2D
	{
	public:
		void static Init();
		void static Shutdown();
		void static BeginScene(const OrthographicCamera& camera);
		void static EndScene();

		// primitives
		void static DrawQuad(const glm::vec2& position, const glm::vec2& scale, const glm::vec4& color = { 0.5f, 0.5f, 0.5f, 1.0f } );
		void static DrawQuad(const glm::vec3& position, const glm::vec2& scale, const glm::vec4& color = { 0.5f, 0.5f, 0.5f, 1.0f });
		void static DrawQuad(const glm::vec2& position, const glm::vec2& scale, const Ref<Texture> texture);
		void static DrawQuad(const glm::vec3& position, const glm::vec2& scale, const Ref<Texture> texture);
	};
}

