#include "lxpch.h"
#include "Application.h"
#include "Lux/Events/ApplicationEvent.h"
#include "Lux/Log.h"

namespace Lux
{
	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		if(e.IsInCategory(EventCategory::EventCategoryApplication))
			LX_TRACE(e);
		if(e.IsInCategory(EventCategory::EventCategoryInput))
			LX_TRACE(e);
		while (true);
	}

	Application* CreateApplication();
}