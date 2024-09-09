#pragma once
#include "Layer.h"
#include "Renderer/Camera.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include "Renderer/VertexArray.h"

namespace Quiet 
{
	class Game : public Layer
	{
	public:
		Game();
		void OnAttach() override;
		void OnDetach() override;

		void OnUpdate(Timestep ts) override;
		void OnEvent(Event& e) override;

	private:
		std::shared_ptr<Camera> m_Camera;

		std::shared_ptr<Shader>		m_TestShader;
		std::shared_ptr<Texture2D>	m_TestTexture;
		std::shared_ptr<VertexArray>	m_VertexArray;

		// Still fucking hardcoded
		std::string VertexPath = R"(D:\Code\Shooter_OpenGL\Engine\Assets\Shaders\VertexShader.glsl)";
		std::string FragmentPath = R"(D:\Code\Shooter_OpenGL\Engine\Assets\Shaders\FragShader.glsl)";
		std::string TexturePath = R"(D:\Code\Shooter_OpenGL\Engine\Assets\Textures\container.jpg)";
	};
}
