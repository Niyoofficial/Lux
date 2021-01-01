#pragma once

#include "Lux/Renderer/RendererAPI.h"

namespace Lux
{
	class OpenGLRendererAPI : public RendererAPI
	{
		virtual void SetClearColor(glm::vec4 color) override;
		virtual void Clear() override;
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
	};
}
