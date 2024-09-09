#pragma once

struct GLFWwindow;

namespace Quiet
{
	class GraphicsContext
	{
	public:
		GraphicsContext(GLFWwindow* WindowHandle);
		~GraphicsContext() = default;

		void Init();
		void SwapBuffers();

	private:
		GLFWwindow* m_WindowHandle;
	};
}
