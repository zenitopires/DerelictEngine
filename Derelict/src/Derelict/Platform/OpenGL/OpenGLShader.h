#pragma once

#include "../../Renderer/Shader.h"

#include <glm/gtc/matrix_transform.hpp>

#include <string>

namespace Derelict {
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(std::string_view vertexSource, std::string_view fragmentSource);
		virtual ~OpenGLShader() override;
		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void UploadMat4(std::string_view name, const glm::mat4& matrix);
		void UploadFloat3(std::string_view name, const glm::vec3& values);
		void UploadInt(std::string_view name, int value);
		virtual void UploadFloat4(std::string_view name, const glm::vec4& values);

	private:
		uint32_t m_RendererID;
	};
}

