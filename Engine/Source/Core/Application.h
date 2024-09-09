#pragma once

#include "Renderer/Buffer.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include "Renderer/VertexArray.h"

#include "Renderer/Camera.h"
#include "Renderer/Window.h"

namespace Quiet
{
	class Application
	{
	public:
		Application(const std::string& name);

		void OnEvent(Event& event);
		void Run();

		static Application& Get() { return *s_Instance; }
		Window& GetWindow() { return *m_Window; }

	private:
		bool OnWindowClose(WindowCloseEvent& event);
		bool OnWindowResize(WindowResizeEvent& event);

		static Application* s_Instance;
		std::unique_ptr<Window> m_Window;

		bool m_Running = true;
		
		std::shared_ptr<Shader>		m_TestShader;
		std::shared_ptr<Texture2D>	m_TestTexture;

		std::shared_ptr<VertexArray>	m_VertexArray;
		std::shared_ptr<VertexBuffer>	m_VertexBuffer;
		std::shared_ptr<IndexBuffer>	m_IndexBuffer;

		// Still fucking hardcoded
		std::string VertexPath = R"(D:\Code\Shooter_OpenGL\Engine\Assets\Shaders\VertexShader.glsl)";
		std::string FragmentPath = R"(D:\Code\Shooter_OpenGL\Engine\Assets\Shaders\FragShader.glsl)";
		std::string TexturePath = R"(D:\Code\Shooter_OpenGL\Engine\Assets\Textures\container.jpg)";
	};
}
