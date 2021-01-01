#include "lxpch.h"
#include "OpenGLContext.h"

#include "glfw/glfw3.h"
#include <glad/glad.h>

Lux::OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
	:m_WindowHandle(windowHandle)
{
	LX_CORE_ASSERT(m_WindowHandle, "Window handle is null!");
}

void Lux::OpenGLContext::Init()
{
	glfwMakeContextCurrent(m_WindowHandle);
	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	LX_CORE_ASSERT(status, "");

	LX_CORE_INFO("OpenGL info:");
	LX_CORE_INFO("Vendor: {0}", glGetString(GL_VENDOR));
	LX_CORE_INFO("Renderer: {0}", glGetString(GL_RENDERER));
	LX_CORE_INFO("Version: {0}", glGetString(GL_VERSION));
}

void Lux::OpenGLContext::SwapBuffers()
{
	glfwSwapBuffers(m_WindowHandle);
}
