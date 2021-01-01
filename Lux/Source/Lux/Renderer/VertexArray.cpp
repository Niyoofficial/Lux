#include "lxpch.h"
#include "Renderer.h"
#include "VertexArray.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Lux
{
    std::shared_ptr<VertexArray> Lux::VertexArray::Create(const std::shared_ptr<VertexBuffer>& vertexBuffer, const std::shared_ptr<IndexBuffer>& indexBuffer)
    {
        switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			LX_CORE_ASSERT(false, "None type API is not supported!");
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLVertexArray>(vertexBuffer, indexBuffer);
		}
    }
}
