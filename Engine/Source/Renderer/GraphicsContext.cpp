#include "Quiet_PCH.h"
#include "GraphicsContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "Core/Core.h"

namespace Quiet
{
	GraphicsContext::GraphicsContext(GLFWwindow* WindowHandle) : m_WindowHandle(WindowHandle)
	{
		QT_ASSERT(WindowHandle, "Graphics Context::Window Handle is null!")
	}

	void GraphicsContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		QT_ASSERT(status, "Failed to initialize Glad!")

		LOG_INFO("OpenGL::Vendor::{0}", (const char*)glGetString(GL_VENDOR));
		LOG_INFO("OpenGL::Renderer::{0}", (const char*)glGetString(GL_RENDERER));
		LOG_INFO("OpenGL::Version::{0}", (const char*)glGetString(GL_VERSION));

		QT_ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5), "Requires at least OpenGL version 4.5!")
	}

	void GraphicsContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}
