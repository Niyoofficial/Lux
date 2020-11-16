#include "lxpch.h"
#include <GLFW/glfw3.h>
#include "WindowsWindow.h"

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
		Data.Title = Props.Title;
		Data.Width = Props.Width;
		Data.Height = Props.Height;

		LX_CORE_INFO("Creating Window {0} ({1}, {2})", Data.Title, Data.Width, Data.Height);

		if (!s_GLFWInitialized)
		{
			int success = glfwInit();
			LX_CORE_ASSERT(success, "Could not initialize GLFW!");

			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow(Data.Width, Data.Height, Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &Data);
		SetVSync(true);

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* Window, int Width, int Height)
			{
				WindowData& Data = *reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(Window));

				Data.Width = Width;
				Data.Height = Height;

				Data.WindowResizeCallback.Dispatch(Width, Height);
			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* Window)
			{
				WindowData& Data = *reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(Window));
				
				Data.WindowCloseCallback.Dispatch();
			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* Window, int Key, int ScanCode, int Action, int Mods)
			{
				WindowData& Data = *reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(Window));

				switch (Action)
				{
				case GLFW_PRESS:
				{
					Data.KeyPressedCallback.Dispatch(Key);
					break;
				}
				case GLFW_RELEASE:
				{
					Data.KeyReleasedCallback.Dispatch(Key);
					break;
				}
				case GLFW_REPEAT:
				{
					Data.KeyRepeatCallback.Dispatch(Key);
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
					Data.MouseButtonPressedCallback.Dispatch(Key);
					break;
				}
				case GLFW_RELEASE:
				{
					Data.MouseButtonReleasedCallback.Dispatch(Key);
					break;
				}
				}
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* Window, double xOffset, double yOffset)
			{
				WindowData& Data = *reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(Window));
				
				Data.MouseScrolledCallback.Dispatch(xOffset, yOffset);
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* Window, double xPos, double yPos)
			{
				WindowData& Data = *reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(Window));

				Data.MouseMovedCallback.Dispatch(xPos, yPos);
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
		Data.VSyncEnabled = Enabled;
	}

	void WindowsWindow::ShutDown()
	{
		glfwDestroyWindow(m_Window);
	}
}