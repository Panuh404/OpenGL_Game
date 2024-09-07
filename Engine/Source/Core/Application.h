#pragma once

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include "Renderer/Buffer.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include "Renderer/VertexArray.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Renderer/Camera.h"

namespace Quiet
{
	class Application
	{
	public:
		Application(const std::string& name);

		void Run();
		void Shutdown();
		void ProcessInput(GLFWwindow* window);

	private:
		GLFWwindow* m_Window;
		
		std::shared_ptr<Shader>		m_TestShader;
		std::shared_ptr<Texture2D>	m_TestTexture;

		std::shared_ptr<VertexArray>	m_VertexArray;
		std::shared_ptr<VertexBuffer>	m_VertexBuffer;
		std::shared_ptr<IndexBuffer>	m_IndexBuffer;

		std::string VertexPath = R"(D:\Code\Shooter_OpenGL\Engine\Assets\Shaders\VertexShader.glsl)";
		std::string FragmentPath = R"(D:\Code\Shooter_OpenGL\Engine\Assets\Shaders\FragShader.glsl)";
		std::string TexturePath = R"(D:\Code\Shooter_OpenGL\Engine\Assets\Textures\container.jpg)";

	};

	
}