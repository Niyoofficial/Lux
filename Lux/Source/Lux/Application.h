#pragma once

#include "Core.h"

namespace Lux
{
	class LUX_API Application
	{
	public:
		Application() {}
		virtual ~Application() {}
		void Run();
	};

	Application* CreateApplication();
}