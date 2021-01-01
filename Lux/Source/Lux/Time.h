#pragma once

#include <GLFW/glfw3.h>

namespace Lux
{
	class Time
	{
	public:
		static float GetTimeSeconds() { return (float)glfwGetTime(); }
	private:
	};
}
