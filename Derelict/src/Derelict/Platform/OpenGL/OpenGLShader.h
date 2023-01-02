#pragma once

#include "../../Renderer/Shader.h"

namespace Derelict {
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(std::string_view vertexSource, std::string_view fragmentSource);
		virtual ~OpenGLShader() override;
		virtual void Bind() const override;
		virtual void Unbind() const override;

	private:
		uint32_t m_RendererID;
	};
}

