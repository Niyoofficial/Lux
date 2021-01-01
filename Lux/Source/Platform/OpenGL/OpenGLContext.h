#pragma once

#include "Lux/Renderer/RenderingContext.h"

struct GLFWwindow;

namespace Lux
{
	class OpenGLContext : public RenderingContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};
}
