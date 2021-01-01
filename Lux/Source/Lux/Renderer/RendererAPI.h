#pragma once

#include <D:\Documents\VisualStudio\Projects\Lux\Lux\Vendor\glm\glm\glm.hpp>
#include <memory>
#include "VertexArray.h"

namespace Lux
{
	class RendererAPI
	{
	public:
		enum class API
		{
			None, OpenGL
		};
	public:
		virtual void SetClearColor(glm::vec4 color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

		inline static API GetAPI() { return s_API; }
	private:
		static API s_API;
	};
}
