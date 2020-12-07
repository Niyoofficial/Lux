#pragma once

#include "Lux/Window.h"

namespace Lux
{
	class LUX_API WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& Props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		inline void SetEventCallback(const EventCallbackFn& Callback) override { m_Data.EventCallback = Callback; }
		void SetVSync(bool Enabled) override;
		inline bool IsVSync() const override { return m_Data.VSyncEnabled; }

	private:
		virtual void Init(const WindowProps& Props);
		virtual void ShutDown();

	private:
		struct GLFWwindow* m_Window;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSyncEnabled;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};
}