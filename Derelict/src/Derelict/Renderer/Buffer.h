#pragma once

#include <vector>
#include <cstdint>
#include <string>

namespace Derelict {
	enum class ShaderDataType
	{
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:		return 4;
		case ShaderDataType::Float2:	return 8;
		case ShaderDataType::Float3:	return 12;
		case ShaderDataType::Float4:	return 16;
		case ShaderDataType::Mat3:		return 36;
		case ShaderDataType::Mat4:		return 64;
		case ShaderDataType::Int:		return 4;
		case ShaderDataType::Int2:		return 8;
		case ShaderDataType::Int3:		return 12;
		case ShaderDataType::Int4:		return 16;
		case ShaderDataType::Bool:		return 1;
		}

		return 0;
	}

	struct VertexAttribute
	{
		ShaderDataType Type;
		bool Normalized;
		uint32_t Offset;
		uint32_t Size;

		VertexAttribute() = default;
		VertexAttribute(ShaderDataType type, std::string_view name, bool normalized = false)
			: Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
		{
		}

		uint32_t GetComponentCount() const
		{
			switch (Type)
			{
			case ShaderDataType::Float:		return 1;
			case ShaderDataType::Float2:	return 2;
			case ShaderDataType::Float3:	return 3;
			case ShaderDataType::Float4:	return 4;
			case ShaderDataType::Mat3:		return 9;
			case ShaderDataType::Mat4:		return 16;
			case ShaderDataType::Int:		return 1;
			case ShaderDataType::Int2:		return 2;
			case ShaderDataType::Int3:		return 3;
			case ShaderDataType::Int4:		return 4;
			case ShaderDataType::Bool:		return 1;
			}
		}
	};

	class AttributeLayout
	{
	public:
		AttributeLayout() = default;
		AttributeLayout(const std::initializer_list<VertexAttribute>& elements)
			: m_Attributes(elements)
		{
			CalculateOffsetsAndStride();
		}

		inline const std::vector<VertexAttribute>& GetElements() const { return m_Attributes; }
		inline const uint32_t GetStride() const { return m_Stride; }

		std::vector<VertexAttribute>::iterator begin() { return m_Attributes.begin(); }
		std::vector<VertexAttribute>::iterator end() { return m_Attributes.end(); }
		std::vector<VertexAttribute>::const_iterator begin() const { return m_Attributes.begin(); }
		std::vector<VertexAttribute>::const_iterator end() const { return m_Attributes.end(); }

	private:
		void CalculateOffsetsAndStride()
		{
			uint32_t offset = 0;
			m_Stride = 0;
			for (auto& attribute : m_Attributes)
			{
				attribute.Offset = offset;
				offset += attribute.Size;
				m_Stride += attribute.Size;
			}
		}
	private:
		std::vector<VertexAttribute> m_Attributes;
		uint32_t m_Stride;
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}
		
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		// Associate the the vertex attribute layout with the vertex buffer.
		virtual void SetLayout(const AttributeLayout& layout) = 0;
		virtual const AttributeLayout& GetLayout() const = 0;

		static VertexBuffer* Create(float* vertices, uint32_t size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static IndexBuffer* Create(uint32_t* indices, uint32_t count);
	};
}

