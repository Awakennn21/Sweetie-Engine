#include "pch.h"
#include "OpenGlContext.h"
#include "Sweetie_c/Core.h"
#include "Sweetie_c/Log.h"

#include <glad/glad.h>
namespace Sweetie
{
	OpenGlContext::OpenGlContext(GLFWwindow* WindowHandle)
		:m_WindowHandle(WindowHandle)
	{
		SW_CORE_ASSERT(WindowHandle, "Window handle is NULL");
		this->Init();
	}
	void OpenGlContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		SW_CORE_ASSERT(status, "Failed to initialize GLAD");
	}
	void OpenGlContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}

