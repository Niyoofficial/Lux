#pragma once

#include "Lux/Renderer/RenderCommand.h"
#include "Lux/Renderer/Camera.h"
#include "Shader.h"

namespace Lux
{
	class Renderer
	{
	public:
		static void BeginScene(const glm::mat4& vp);
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); };
	private:
		static glm::mat4 m_ViewProjectionMatrix;
	};
}
