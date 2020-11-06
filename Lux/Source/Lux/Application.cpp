#include "lxpch.h"
#include "Application.h"
#include "Lux/Events/ApplicationEvent.h"
#include "Lux/Log.h"
#include <GLFW/glfw3.h>

namespace Lux
{
	Application::Application()
		:m_Window(std::unique_ptr<Window>(Window::Create()))
	{
		m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
	}

	Application::~Application()
	{
	}

	void Application::OnEvent(Event& event)
	{
		EventDispacher Dispatcher(event);
		Dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));

		LX_CORE_TRACE("{0}", event.ToString());
	}

	bool Application::OnWindowClose(WindowCloseEvent& event)
	{
		m_Running = false;
		return true;
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