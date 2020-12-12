#include "lxpch.h"
#include "WindowsInput.h"
#include "Lux/Application.h"
#include <GLFW/glfw3.h>

namespace Lux
{
	Input* Input::s_Instance = new WindowsInput;

	bool WindowsInput::IsKeyPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return { xpos, ypos };
	}

	float WindowsInput::GetMouseXImpl()
	{
		return GetMousePositionImpl().first;
	}

	float WindowsInput::GetMouseYImpl()
	{
		return GetMousePositionImpl().second;
	}
}