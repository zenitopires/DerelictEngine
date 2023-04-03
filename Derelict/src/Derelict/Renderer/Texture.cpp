#include "Texture.h"
#include "../Core/Core.h"

#include "../Platform/OpenGL/OpenGLTexture2D.h"

#include <string>

namespace Derelict {

	Ref<Texture2D> Texture2D::Create(const std::string_view path)
	{
		return std::make_shared<OpenGLTexture2D>(path);
	}

	Derelict::Ref<Derelict::Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		return std::make_shared<OpenGLTexture2D>(width, height);
	}

}