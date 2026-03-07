#ifdef PLB_PLATFORM_WND
#include "platform/windows/wnd_window.h"

#include <GLFW/glfw3.h>
#include "core/events/event_list.h"
#include "core/debug/assert_macros.h"
#include "core/debug/log_macros.h"

namespace plb
{
	WndWindow::WndWindow()
	{
		if (!glfwInit())
		{
			PLB_LOG_ERROR("Window", "Unable to init GLFW");
			return;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // PLB_TODO: chage versions and profiles for macros

#ifdef PLB_PLATFORM_MAC
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	}

	WndWindow::~WndWindow()
	{
		glfwDestroyWindow(m_Window);
	}

	void WndWindow::build(WinSpecs&& specs)
	{
		if (!m_PushEvent)
		{
			PLB_LOG_ERROR("Window", "Unable to build a GLFW window without an event pointer previouslty set");
		}

		m_Window = glfwCreateWindow(specs.width, specs.height, specs.name, specs.fullscreen ? glfwGetPrimaryMonitor() : nullptr, nullptr);
		if (!m_Window)
		{
			PLB_LOG_ERROR("Window", "GLFW window creation at glfwCreateWindow");
			return;
		}

		glfwMakeContextCurrent(m_Window);

		glfwSetWindowUserPointer(m_Window, this);

		// window events
		glfwSetWindowCloseCallback(m_Window, closeCallback);
		glfwSetFramebufferSizeCallback(m_Window, framebufferSizeCallback);

		// cursor inputs
		glfwSetCursorEnterCallback(m_Window, cursorEnterCallback);
		glfwSetCursorPosCallback(m_Window, cursorPosCallback);
		glfwSetScrollCallback(m_Window, scrollCallback);

		// mouse inputs
		glfwSetMouseButtonCallback(m_Window, mouseButtonCallback);

		// key inputs
		glfwSetKeyCallback(m_Window, keyCallback);
	}

	void WndWindow::makeContextCurrent()
	{
		glfwMakeContextCurrent(m_Window);
	}

	void WndWindow::pollEvents()
	{
		glfwPollEvents();
	}

	void WndWindow::swapBuffers()
	{
		glfwSwapBuffers(m_Window);
	}

	float WndWindow::getTime()
	{
		return glfwGetTime();
	}
	
	// window events
	void WndWindow::closeCallback(GLFWwindow* window)
	{
		WndWindow* win = (WndWindow*)glfwGetWindowUserPointer(window);

		if (!win)
		{
			PLB_LOG_ERROR("Window", "Unable to retrieve window user pointer");
			return;
		}

		//win->m_PushEvent(std::make_unique<WindowCloseEvent>);
	}

	void WndWindow::framebufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		WndWindow* win = (WndWindow*)glfwGetWindowUserPointer(window);

		if (!win)
		{
			PLB_LOG_ERROR("Window", "Unable to retrieve window user pointer");
			return;
		}

		//win->m_PushEvent(std::make_unique<WindowResizeEvent>);
	}

	// cursor inputs
	void WndWindow::cursorEnterCallback(GLFWwindow* window, int entered)
	{
		WndWindow* win = (WndWindow*)glfwGetWindowUserPointer(window);

		if (!win)
		{
			PLB_LOG_ERROR("Window", "Unable to retrieve window user pointer");
			return;
		}

		if (entered)
		{
			//win->m_PushEvent(std::make_unique<CursorEnterEvent>());
		}
		else
		{
			//win->m_PushEvent(std::make_unique<CursorExitEvent>());
		}
	}

	void WndWindow::cursorPosCallback(GLFWwindow* window, double xPos, double yPos)
	{
		WndWindow* win = (WndWindow*)glfwGetWindowUserPointer(window);

		if (!win)
		{
			PLB_LOG_ERROR("Window", "Unable to retrieve window user pointer");
			return;
		}

		//win->m_PushEvent(std::make_unique<CursorMoveEvent>());
	}

	void WndWindow::scrollCallback(GLFWwindow* window, double xOffset, double yOffset)
	{
		WndWindow* win = (WndWindow*)glfwGetWindowUserPointer(window);

		if (!win)
		{
			PLB_LOG_ERROR("Window", "Unable to retrieve window user pointer");
			return;
		}

		//win->m_PushEvent(std::make_unique<ScrollEvent>());
	}

	// mouse inputs
	void WndWindow::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		WndWindow* win = (WndWindow*)glfwGetWindowUserPointer(window);

		if (!win)
		{
			PLB_LOG_ERROR("Window", "Unable to retrieve window user pointer");
			return;
		}

		if (action == GLFW_PRESS)
		{
			//win->m_PushEvent(std::make_unique<ClickDownEvent>(button, mods));
		}
		else
		{
			//win->m_PushEvent(std::make_unique<ClickReleaseEvent>(button));
		}
	}

	// key inputs
	void WndWindow::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		WndWindow* win = (WndWindow*)glfwGetWindowUserPointer(window);

		if (!win)
		{
			PLB_LOG_ERROR("Window", "Unable to retrieve window user pointer");
			return;
		}

		switch (action)
		{
			case GLFW_PRESS:
			{
				//win->m_PushEvent(std::make_unique<KeyPressEvent>(key, mods));
				break;
			}
			case GLFW_REPEAT:
			{
				//win->m_PushEvent(std::make_unique<KeyPressEvent>());
				break;
			}
			case GLFW_RELEASE:
			{
				//win->m_PushEvent(std::make_unique<KeyReleaseEvent>(key));
				break;
			}
		}
	}
}
#endif