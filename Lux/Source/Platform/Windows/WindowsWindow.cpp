#include "lxpch.h"
#include <GLFW/glfw3.h>
#include "WindowsWindow.h"
#include "Lux/Events/ApplicationEvent.h"
#include "Lux/Events/KeyEvent.h"
#include "Lux/Events/MouseEvent.h"

#include "glad/glad.h"

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
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		LX_CORE_ASSERT(status, "")
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int Width, int Height)
			{
				WindowData& m_Data = *reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(window));

				m_Data.Width = Width;
				m_Data.Height = Height;

				m_Data.EventCallback(WindowResizeEvent(Width, Height));
			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				WindowData& m_Data = *reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(window));
				
				m_Data.EventCallback(WindowCloseEvent());
			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int Key, int ScanCode, int Action, int Mods)
			{
				WindowData& m_Data = *reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(window));

				static unsigned int repeatCount;
				switch (Action)
				{
				case GLFW_PRESS:
				{
					repeatCount = 0;
					m_Data.EventCallback(KeyPressedEvent(Key, 0));
					break;
				}
				case GLFW_RELEASE:
				{
					repeatCount = 0;
					m_Data.EventCallback(KeyReleasedEvent(Key));
					break;
				}
				case GLFW_REPEAT:
				{
					repeatCount++;
					m_Data.EventCallback(KeyPressedEvent(Key, repeatCount));
					break;
				}
				}
			});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int c)
			{
				WindowData& m_Data = *reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(window));
				m_Data.EventCallback(KeyTypedEvent(c));
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int Key, int Action, int Mods)
			{
				WindowData& m_Data = *reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(window));

				switch (Action)
				{
				case GLFW_PRESS:
				{
					m_Data.EventCallback(MouseButtonPressedEvent(Key));
					break;
				}
				case GLFW_RELEASE:
				{
					m_Data.EventCallback(MouseButtonReleasedEvent(Key));
					break;
				}
				case GLFW_REPEAT:
				{
					m_Data.EventCallback(MouseButtonPressedEvent(Key));
					break;
				}
				}
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& m_Data = *reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(window));
				
				m_Data.EventCallback(MouseScrolledEvent(xOffset, yOffset));
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData& m_Data = *reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(window));

				m_Data.EventCallback(MouseMovedEvent(xPos, yPos));
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