#include "VertexArray.h"
#include "../Platform/OpenGL/OpenGLVertexArray.h"

namespace Derelict {

	Ref<VertexArray> VertexArray::Create()
	{
		return std::make_shared<OpenGLVertexArray>();
	}

}