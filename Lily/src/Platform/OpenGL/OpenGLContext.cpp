#include "llpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Lily {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		LL_CORE_ASSERT(windowHandle, "WindowHandle is null");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		LL_CORE_ASSERT(status, "Failed to initialize Glad!");

		LL_CORE_INFO("OpenGL Info:");
		LL_CORE_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		LL_CORE_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		LL_CORE_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}