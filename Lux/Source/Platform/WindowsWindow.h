#pragma once

#include "Lux/Window.h"
#include "Lux/Event.h"

namespace Lux
{
	class LUX_API WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& Props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return Data.Width; }
		inline unsigned int GetHeight() const override { return Data.Height; }

		void SetVSync(bool Enabled) override;
		inline bool IsVSync() const override { return Data.VSyncEnabled; }

	private:
		virtual void Init(const WindowProps& Props);
		virtual void ShutDown();

	private:
		struct GLFWwindow* m_Window;
	};
}