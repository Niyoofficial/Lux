#pragma once

#include "lxpch.h"

#include "Lux/Core.h"
#include "Lux/Events/Event.h"
#include "Lux/EventDispatcher.h"

namespace Lux
{
	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& WindowTitle = "Lux Engine", unsigned int WindowWidth = 1280, unsigned int WindowHeight = 720)
			: Title(WindowTitle), Width(WindowWidth), Height(WindowHeight) {}
	};

	//Interface representing a desktop system based window
	class LUX_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& Callback) = 0;
		virtual void SetVSync(bool Enabled) = 0;
		virtual bool IsVSync() const = 0;

		static Window* Create(const WindowProps& Props = WindowProps());

		virtual void* GetNativeWindow() = 0;
	};
}