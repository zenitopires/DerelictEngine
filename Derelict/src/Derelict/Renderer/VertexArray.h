#pragma once

namespace Derelict {
	class VertexArray
	{
	public:
		~VertexArray() {}
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		static VertexArray* Create();
	};
}

