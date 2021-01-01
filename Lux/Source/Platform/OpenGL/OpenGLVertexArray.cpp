#include "lxpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Lux
{
    GLenum ShaderTypeToOpenGLType(ShaderDataType type)
    {
        switch (type)
        {
        case Lux::ShaderDataType::None:		return 0;
        case Lux::ShaderDataType::Float:	return GL_FLOAT;
        case Lux::ShaderDataType::Float2:	return GL_FLOAT;
        case Lux::ShaderDataType::Float3:	return GL_FLOAT;
        case Lux::ShaderDataType::Float4:	return GL_FLOAT;
        case Lux::ShaderDataType::Mat3:		return GL_FLOAT;
        case Lux::ShaderDataType::Mat4:		return GL_FLOAT;
        case Lux::ShaderDataType::Int:		return GL_INT;
        case Lux::ShaderDataType::Int2:		return GL_INT;
        case Lux::ShaderDataType::Int3:		return GL_INT;
        case Lux::ShaderDataType::Int4:		return GL_INT;
        case Lux::ShaderDataType::Bool:		return GL_BOOL;
        default: LX_CORE_ASSERT(false, "nknown data type!"); return 0;
        }
    }

    OpenGLVertexArray::OpenGLVertexArray(const std::shared_ptr<VertexBuffer>& vertexBuffer, const std::shared_ptr<IndexBuffer>& indexBuffer)
    {
        LX_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout assigned!");

        glGenVertexArrays(1, &m_RendererID);
        glBindVertexArray(m_RendererID);

        vertexBuffer->Bind();
        m_VertexBuffer = vertexBuffer;
        indexBuffer->Bind();
        m_IndexBuffer = indexBuffer;

        uint32_t index = 0;
        for (const auto& element : vertexBuffer->GetLayout().GetElements())
        {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index, element.GetComponentCount(), ShaderTypeToOpenGLType(element.Type), GL_FALSE, vertexBuffer->GetLayout().GetStride(), (const void*)element.Offset);
            index++;
        }
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        glDeleteVertexArrays(1, &m_RendererID);
    }

    void OpenGLVertexArray::Bind() const
    {
        glBindVertexArray(m_RendererID);
    }

    void OpenGLVertexArray::Unbind() const
    {
        glBindVertexArray(0);
    }
}
