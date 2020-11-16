#pragma once

#include "lxpch.h"

#include "Lux/Core.h"
#include "Lux/Event.h"

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
		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetVSync(bool Enabled) = 0;
		virtual bool IsVSync() const = 0;

		static Window* Create(const WindowProps& Props = WindowProps());

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSyncEnabled;

			EventDispatcher<int, int> WindowResizeCallback;
			EventDispatcher<> WindowCloseCallback;
			EventDispatcher<int> KeyPressedCallback;
			EventDispatcher<int> KeyReleasedCallback;
			EventDispatcher<int> KeyRepeatCallback;
			EventDispatcher<int> MouseButtonPressedCallback;
			EventDispatcher<int> MouseButtonReleasedCallback;
			EventDispatcher<int, int> MouseScrolledCallback;
			EventDispatcher<int, int> MouseMovedCallback;
		};	

		WindowData Data;
	};
}