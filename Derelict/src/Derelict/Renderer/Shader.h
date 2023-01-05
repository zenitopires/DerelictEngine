#pragma once

#include <glm/glm.hpp>

#include <string>

namespace Derelict {
	class Shader
	{
	public:
		virtual ~Shader() {}
		static Shader* Create(std::string_view vertexSource, std::string_view fragmentSource);
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual void UploadMat4(std::string_view name, const glm::mat4& matrix) = 0;

	private:
		uint32_t m_RendererID;
	};
}

