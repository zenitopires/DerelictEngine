#pragma once

#include "../../Renderer/Texture.h"

#include <glad/glad.h>

namespace Derelict {
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(std::string_view path);
		OpenGLTexture2D(uint32_t width, uint32_t height);
		virtual ~OpenGLTexture2D() override;

		virtual uint32_t GetWidth() const override { return m_Width; };
		virtual uint32_t GetHeight() const override { return m_Height; }

		virtual void SetData(void* data, uint32_t size) override;

		virtual void Bind(uint32_t slot) const override;
		virtual void Unbind() const override;

	private:
		uint32_t m_Width, m_Height;
		std::string m_Path;
		uint32_t m_RendererID;
		GLenum m_InternalFormat, m_DataFormat;
	};
}

