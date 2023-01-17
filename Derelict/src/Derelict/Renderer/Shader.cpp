#include "Shader.h"
#include "../Platform/OpenGL/OpenGLShader.h"

namespace Derelict {
	Ref<Shader> Shader::Create(std::string_view name, std::string_view vertexSource, std::string_view fragmentSource)
	{
		return std::make_shared<OpenGLShader>(name, vertexSource, fragmentSource);
	}

	Ref<Shader> Shader::Create(std::filesystem::path path)
	{
		return std::make_shared<OpenGLShader>(path);
	}

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		if (m_Shaders.find(name) != m_Shaders.end())
		{
			// shader already exist
			__debugbreak();
		}
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}


	Derelict::Ref<Derelict::Shader> ShaderLibrary::Load(std::filesystem::path path)
	{
		auto shader = Shader::Create(path);
		Add(shader);
		return shader;
	}

	Derelict::Ref<Derelict::Shader> ShaderLibrary::Load(const std::string& name, std::filesystem::path path)
	{
		auto shader = Shader::Create(path);
		Add(name, shader);
		return shader;
	}

	Derelict::Ref<Derelict::Shader> ShaderLibrary::Get(const std::string& name)
	{
		if (m_Shaders.find(name) == m_Shaders.end())
		{
			__debugbreak();
		}
		return m_Shaders[name];

	}

}