#pragma once

#include <string>
#include <filesystem>

namespace Derelict {
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		
		static Shader* Create(std::filesystem::path path);
		static Shader* Create(std::string_view vertexSource, std::string_view fragmentSource);
	};
}

