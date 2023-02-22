#include "Buffer.h"
#include "../Platform/OpenGL/OpenGLBuffer.h"

namespace Derelict {
	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		return std::make_shared<OpenGLVertexBuffer>(OpenGLVertexBuffer(vertices, size));
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		return new OpenGLIndexBuffer(indices, count);
	}
}