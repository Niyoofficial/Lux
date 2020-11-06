#include "lxpch.h"
#include <GLFW/glfw3.h>
#include "WindowsWindow.h"
#include "Lux/Events/ApplicationEvent.h"
#include "Lux/Events/KeyEvent.h"
#include "Lux/Events/MouseEvent.h"

namespace Lux
{
	static bool s_GLFWInitialized = false;

	WindowsWindow::WindowsWindow(const WindowProps& Props)
	{
		Init(Props);
	}

	WindowsWindow::~WindowsWindow()
	{
		ShutDown();
	}

	Window* Window::Create(const WindowProps& Props)
	{
		return new WindowsWindow(Props);
	}

	void WindowsWindow::Init(const WindowProps& Props)
	{
		m_Data.Title = Props.Title;
		m_Data.Width = Props.Width;
		m_Data.Height = Props.Height;

		LX_CORE_INFO("Creating Window {0} ({1}, {2})", m_Data.Title, m_Data.Width, m_Data.Height);

		if (!s_GLFWInitialized)
		{
			int success = glfwInit();
			LX_CORE_ASSERT(success, "Could not initialize GLFW!");

			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* Window, int Width, int Height)
			{
				WindowData& Data = *reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(Window));

				Data.Width = Width;
				Data.Height = Height;

				Data.EventCallback(WindowResizeEvent(Width, Height));
			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* Window)
			{
				WindowData& Data = *reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(Window));
				
				Data.EventCallback(WindowCloseEvent());
			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* Window, int Key, int ScanCode, int Action, int Mods)
			{
				WindowData& Data = *reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(Window));

				switch (Action)
				{
				case GLFW_PRESS:
				{
					Data.EventCallback(KeyPressedEvent(Key, 0));
					break;
				}
				case GLFW_RELEASE:
				{
					Data.EventCallback(KeyReleasedEvent(Key));
					break;
				}
				case GLFW_REPEAT:
				{
					Data.EventCallback(KeyPressedEvent(Key, 1));
					break;
				}
				}
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* Window, int Key, int Action, int Mods)
			{
				WindowData& Data = *reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(Window));
				switch (Action)
				{
				case GLFW_PRESS:
				{
					Data.EventCallback(MouseButtonPressedEvent(Key));
					break;
				}
				case GLFW_RELEASE:
				{
					Data.EventCallback(MouseButtonReleasedEvent(Key));
					break;
				}
				}
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* Window, double xOffset, double yOffset)
			{
				WindowData& Data = *reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(Window));
				
				Data.EventCallback(MouseScrolledEvent(xOffset, yOffset));
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* Window, double xPos, double yPos)
			{
				WindowData& Data = *reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(Window));

				Data.EventCallback(MouseMovedEvent(xPos, yPos));
			});
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetVSync(bool Enabled)
	{
		if(Enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);
		m_Data.VSyncEnabled = Enabled;
	}

	void WindowsWindow::ShutDown()
	{
		glfwDestroyWindow(m_Window);
	}
}