#pragma once

#include <string>

namespace Derelict {
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		
		static Shader* Create(std::string_view vertexSource, std::string_view fragmentSource);
	};
}

