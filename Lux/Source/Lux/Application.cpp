#include "lxpch.h"
#include "Application.h"
#include "Lux/Log.h"
#include <glad/glad.h>
#include "Events/ApplicationEvent.h"

namespace Lux
{
	Application* Application::s_Instance = nullptr;

	Application::Application()
		:m_Window(std::unique_ptr<Window>(Window::Create()))
	{
		LX_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
	}

	Application::~Application()
	{
	}

	void Application::OnEvent(Event& e)
	{
		if (e.GetEventType() == Lux::EventType::WindowClose)
			m_Running = false;

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.IsHandled())
				break;
		}
	}

	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_Window->OnUpdate();
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	Application* CreateApplication();
}