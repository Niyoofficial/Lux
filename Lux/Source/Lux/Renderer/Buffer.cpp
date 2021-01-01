#include "lxpch.h"
#include "Buffer.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Lux
{
	VertexBuffer* Lux::VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			LX_CORE_ASSERT(false, "None type API is not supported!");
		case RendererAPI::API::OpenGL:
			return new OpenGLVertexBuffer(vertices, size);
		}
	}

	IndexBuffer* Lux::IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			LX_CORE_ASSERT(false, "None type API is not supported!");
		case RendererAPI::API::OpenGL:
			return new OpenGLIndexBuffer(indices, count);
		}
	}
}
