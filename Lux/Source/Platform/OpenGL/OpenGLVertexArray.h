#pragma once
#include "Lux/Renderer/VertexArray.h"

namespace Lux
{
    class OpenGLVertexArray : public VertexArray
    {
    public:
        OpenGLVertexArray(const std::shared_ptr<VertexBuffer>& vertexBuffer, const std::shared_ptr<IndexBuffer>& indexBuffer);
        virtual ~OpenGLVertexArray();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual const std::shared_ptr<VertexBuffer>& GetVertexBuffer() const override { return m_VertexBuffer; }
        virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; }
    private:
        uint32_t m_RendererID;

        std::shared_ptr<VertexBuffer> m_VertexBuffer;
        std::shared_ptr<IndexBuffer> m_IndexBuffer;
    };
}
