#pragma once

#include "../../Renderer/Shader.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>

#include <string>
#include <unordered_map>

namespace Derelict {
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(std::string_view name, std::string_view vertexSource, std::string_view fragmentSource);
		OpenGLShader(std::filesystem::path path);
		virtual ~OpenGLShader() override;
		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual const std::string GetName() const override { return m_Name; }

		virtual void UploadMat4(std::string_view name, const glm::mat4& matrix);
		void UploadFloat3(std::string_view name, const glm::vec3& values);
		void UploadInt(std::string_view name, int value);
		virtual void UploadFloat4(std::string_view name, const glm::vec4& values);

	private:
		std::string ReadFile(std::filesystem::path path);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		void Compile(std::unordered_map<GLenum, std::string>& shaderSources);

	private:
		uint32_t m_RendererID;
		std::string m_Name;
	};
}

