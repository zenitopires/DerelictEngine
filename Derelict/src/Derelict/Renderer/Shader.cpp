#include "Shader.h"
#include "../Platform/OpenGL/OpenGLShader.h"

namespace Derelict {
	Derelict::Shader* Shader::Create(std::string_view vertexSource, std::string_view fragmentSource)
	{
		return new OpenGLShader(vertexSource, fragmentSource);
	}
}