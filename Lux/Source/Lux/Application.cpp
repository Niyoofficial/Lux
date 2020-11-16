#include "lxpch.h"
#include "Application.h"
#include "Lux/Log.h"
#include <GLFW/glfw3.h>

namespace Lux
{
	Application::Application()
		:m_Window(std::unique_ptr<Window>(Window::Create()))
	{
		m_Window->Data.WindowCloseCallback.Bind([this]() { m_Running = false; });
		m_Window->Data.MouseMovedCallback.Bind([](int x, int y) { std::cout << "x: " << x << " y: " << y << std::endl; });
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (m_Running)
		{
			m_Window->OnUpdate();
		}
	}

	Application* CreateApplication();
}