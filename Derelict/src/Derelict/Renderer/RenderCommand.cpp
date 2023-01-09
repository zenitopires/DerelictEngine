#include "RenderCommand.h"

#include "../Platform/OpenGL/OpenGLRendererAPI.h"

namespace Derelict {
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}