#pragma once

#include <string>
#include <unordered_map>
#include <filesystem>

#include <glm/glm.hpp>

#include "../Core/Core.h"


namespace Derelict {
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetFloat3(std::string_view name, const glm::vec3& value) = 0;
		virtual void SetFloat4(std::string_view name, const glm::vec4& value) = 0;
		virtual void SetMat4(std::string_view name, const glm::mat4& value) = 0;
		virtual void SetInt(std::string_view name, uint8_t slot) = 0;

		virtual const std::string GetName() const = 0;
		
		static Ref<Shader> Create(std::filesystem::path path);
		static Ref<Shader> Create(std::string_view name, std::string_view vertexSource, std::string_view fragmentSource);
	};

	class ShaderLibrary
	{
	public:
		void Add(const std::string& name, const Ref<Shader>& shader);
		void Add(const Ref<Shader>& shader);
		Ref<Shader> Load(std::filesystem::path path);
		Ref<Shader> Load(const std::string& name, std::filesystem::path path);

		Ref<Shader> Get(const std::string& name);
	private:
		std::unordered_map < std::string, Ref<Shader>> m_Shaders;
	};
}

