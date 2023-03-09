#include "pch.h"
#include "WindowsWindow.h"
#include "Sweetie_c/Events/KeyboardEvent.h"
#include "Sweetie_c/Events/WindowEvents.h"
#include "Sweetie_c/Events/MouseEvent.h"
#include "Platform/OpenGl/OpenGlContext.h"


namespace Sweetie
{
	static bool GLFWInitialized = false;
	Window* Window::Create(const WindowProperties& props)
	{
		return new WindowsWindow(props);
	}

	Sweetie::WindowsWindow::WindowsWindow(const WindowProperties& Props)
	{
		m_Data.Height = Props.Height;
		m_Data.Width = Props.Width;
		m_Data.Title = Props.Title;

		SW_CORE_INFO("Initialized Window {0} ({1} {2})", m_Data.Title, m_Data.Height, m_Data.Width);

		if (!GLFWInitialized)
		{
			int success = glfwInit();
			SW_CORE_ASSERT(success, "Could Not Initialize GLFW");
			GLFWInitialized = true;
		}
		m_Window = glfwCreateWindow((int)m_Data.Width, (int)m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
		m_Context = new OpenGlContext(m_Window);

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Height = height;

				EventWindowResize event(width, height);
				data.EventCallback(event);
			});
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				EventWindowClose event;
				data.EventCallback(event);
			});
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
					case GLFW_PRESS:
					{
						EventKeyPressed event(key, 0);
						data.EventCallback(event);
					}
					break;

					case GLFW_RELEASE:
					{
						EventKeyReleased event(key);
						data.EventCallback(event);
					}
					break;

					case GLFW_REPEAT:
					{
						EventKeyPressed event(key, 1);//extract repeat count
						data.EventCallback(event);
					}
					break;
				}
			});
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					EventMouseButtonPressed event(button);
					data.EventCallback(event);
				}
				break;

				case GLFW_RELEASE:
				{
					EventMouseButtonReleased event(button);
					data.EventCallback(event);
				}
				break;
				}
			});
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				EventMouseScrolled event((float)xoffset, (float)yoffset);
				data.EventCallback(event);
			});
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				EventMouseMoved event((float)xpos, (float)ypos);
				data.EventCallback(event);
			});
	}

	void Sweetie::WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		m_Context->SwapBuffers();
	}

	void Sweetie::WindowsWindow::SetVSync(bool enabled)
	{
		glfwSwapInterval(enabled);
		m_Data.VSync = enabled;
	}

	bool Sweetie::WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

	Sweetie::WindowsWindow::~WindowsWindow()
	{
		glfwDestroyWindow(m_Window);
	}

}
