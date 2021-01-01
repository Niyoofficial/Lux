#include "lxpch.h"
#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Lux
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}
