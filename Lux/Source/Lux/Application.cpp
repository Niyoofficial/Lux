#include "lxpch.h"
#include "Application.h"
#include "Lux/Log.h"
#include "Events/ApplicationEvent.h"
#include "Lux/Time.h"

namespace Lux
{
	Application* Application::s_Instance = nullptr;

	Application::Application()
		:m_Window(std::unique_ptr<Window>(Window::Create()))
	{
		LX_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window->SetEventCallback(LX_BIND_METHOD(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer;
		PushOverlay(m_ImGuiLayer);
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
			RenderCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.f));
			RenderCommand::Clear();

			float delta = Time::GetTimeSeconds() - m_LastFrameTime;
			m_LastFrameTime = Time::GetTimeSeconds();

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(delta);

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate(delta);
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
	}

	Application* CreateApplication();
}