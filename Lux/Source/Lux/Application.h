#pragma once

#include "Core.h"
#include "Platform/WindowsWindow.h"
#include "Lux/Window.h"
#include "Lux/Events/ApplicationEvent.h"

namespace Lux
{
	class LUX_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& event);
		bool OnWindowClose(WindowCloseEvent& event);

	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	Application* CreateApplication();
}