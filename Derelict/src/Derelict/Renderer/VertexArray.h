#pragma once

#include "Buffer.h"

#include <memory>

namespace Derelict {


	class VertexArray
	{
	public:
		~VertexArray() {}
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;
		static VertexArray* Create();
	};


}

