#include "Buffer.h"
#include "../Platform/OpenGL/OpenGLBuffer.h"

namespace Derelict {
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		return new OpenGLVertexBuffer(vertices, size);
	}
}