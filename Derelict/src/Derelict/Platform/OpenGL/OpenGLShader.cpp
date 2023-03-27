#include "OpenGLShader.h"

#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <array>
#include <iostream>
#include <fstream>

namespace Derelict {

	static GLenum ShaderTypeFromString(const std::string& type)
	{
		if (type == "vertex") return GL_VERTEX_SHADER;
		if (type == "fragment" || type == "pixel") return GL_FRAGMENT_SHADER;

		// Unknown shader type
		__debugbreak();
	}

	OpenGLShader::OpenGLShader(std::string_view name, std::string_view vertexSource, std::string_view fragmentSource)
		: m_Name(name)
	{
		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertexSource;
		sources[GL_FRAGMENT_SHADER] = fragmentSource;
		Compile(sources);
	}

	OpenGLShader::OpenGLShader(std::filesystem::path path)
	{
		std::string source = ReadFile(path);
		auto shaderSources = PreProcess(source);
		Compile(shaderSources);

		m_Name = path.filename().string();
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::SetFloat3(std::string_view name, const glm::vec3& value)
	{
		UploadFloat3(name, value);
	}

	void OpenGLShader::SetFloat4(std::string_view name, const glm::vec4& value)
	{
		UploadFloat4(name, value);
	}

	void OpenGLShader::SetMat4(std::string_view name, const glm::mat4& value)
	{
		UploadMat4(name, value);
	}

	void OpenGLShader::SetInt(std::string_view name, uint8_t slot)
	{
		UploadInt(name, slot);
	}

	void OpenGLShader::UploadMat4(std::string_view name, const glm::mat4& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.data());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadFloat3(std::string_view name, const glm::vec3& values)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.data());
		glUniform3f(location, values.x, values.y, values.z);
	}

	void OpenGLShader::UploadInt(std::string_view name, int value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.data());
		glUniform1i(location, value);
	}

	void OpenGLShader::UploadFloat4(std::string_view name, const glm::vec4& values)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.data());
		glUniform4f(location, values.x, values.y, values.z, values.w);
	}

	std::string OpenGLShader::ReadFile(std::filesystem::path path)
	{
		std::string result;
		std::ifstream in(path.c_str(), std::ios::in | std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);
			result.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();
		}
		else
		{
			std::cout << "Could not open file\n";
		}

		return result;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source)
	{
		const char* typeToken = "#type";
		std::unordered_map<GLenum, std::string> shaderSources;
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);
		while (pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos);
			if (eol != std::string::npos)
			{
				size_t begin = pos + typeTokenLength + 1;
				std::string type = source.substr(begin, eol - begin);

				if (type == "vertex" || type == "fragment" || type == "pixel")
				{
					size_t nextLinePos = source.find_first_not_of("\r\n", eol);
					pos = source.find(typeToken, nextLinePos);
					shaderSources[ShaderTypeFromString(type)] =
						source.substr(nextLinePos,
							pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
				}
				else
				{
					__debugbreak();
				}
			}
		}

		return shaderSources;
	}

	void OpenGLShader::Compile(std::unordered_map<GLenum, std::string>& shaderSources)
	{
		if (shaderSources.size() > 2)
		{
			// shader sources should not be greater than 2, only need vertex and fragment shaders
			__debugbreak();
		}

		GLuint program = glCreateProgram();

		std::array<GLenum, 2> shaderIDs;

		uint32_t index = 0;
		for (auto& kv : shaderSources)
		{
			GLenum type = kv.first;
			const std::string& source = kv.second;

			GLuint shader = glCreateShader(type);

			// Send the vertex shader source code to GL
			// Note that std::string's .c_str is NULL character terminated.
			const GLchar* sourceCstr = source.c_str();
			glShaderSource(shader, 1, &sourceCstr, 0);

			// Compile the vertex shader
			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				// The maxLength includes the NULL character
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				// We don't need the shader anymore.
				glDeleteShader(shader);

				std::cerr << infoLog.data() << '\n';
				__debugbreak();
			}

			glAttachShader(program, shader);
			shaderIDs[index++] = shader;
		}
		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		//m_RendererID = program;

		// Link our program
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);
			// Don't leak shaders either.

			for (auto ID : shaderIDs)
			{
				glDeleteShader(ID);
			}

			std::cerr << infoLog.data() << '\n';
			__debugbreak();
		}

		// Always detach shaders after a successful link.
		for (auto ID : shaderIDs)
		{
			glDeleteShader(ID);
		}

		m_RendererID = program;
	}

}