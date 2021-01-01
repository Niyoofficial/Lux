#pragma once

#include "Buffer.h"

namespace Lux
{
	class VertexArray
	{
	public:
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual const std::shared_ptr<VertexBuffer>& GetVertexBuffer() const = 0;
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const = 0;

		static std::shared_ptr<VertexArray> Create(const std::shared_ptr<VertexBuffer>& vertexBuffer, const std::shared_ptr<IndexBuffer>& indexBuffer);
	};
}
