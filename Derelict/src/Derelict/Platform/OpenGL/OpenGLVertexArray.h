#pragma once
#include <cstdint>
#include "../../Renderer/VertexArray.h"

namespace Derelict {
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();
		virtual void Bind() const;
		virtual void Unbind() const;
	private:
		uint32_t m_RendererID;
	};
}

