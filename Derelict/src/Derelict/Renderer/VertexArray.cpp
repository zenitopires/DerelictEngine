#include "VertexArray.h"
#include "../Platform/OpenGL/OpenGLVertexArray.h"

namespace Derelict {

	Derelict::VertexArray* VertexArray::Create()
	{
		return new OpenGLVertexArray();
	}

}