#include "lxpch.h"
#include "Renderer.h"

namespace Lux
{
	glm::mat4 Renderer::m_ViewProjectionMatrix = glm::mat4();

	void Renderer::BeginScene(const glm::mat4& vp)
	{
		m_ViewProjectionMatrix = vp;
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader)
	{
		shader->Bind();
		shader->UploadViewProjectionMatrix(m_ViewProjectionMatrix);
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}
