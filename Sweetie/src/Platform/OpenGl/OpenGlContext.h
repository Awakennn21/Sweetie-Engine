#pragma once
#include "Platform/Rendering/GraphicsContext.h"
#include <GLFW/glfw3.h>

namespace Sweetie
{
	class OpenGlContext : public GraphicsContext
	{
	private:
		GLFWwindow* m_WindowHandle;
	public:
		OpenGlContext(GLFWwindow* WindowHandle);

		virtual void Init();
		virtual void SwapBuffers();
	};
}

