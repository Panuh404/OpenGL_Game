#include "Quiet_PCH.h"
#include "Game.h"

#include "GLFW/glfw3.h"

namespace Quiet
{
	// Settings
	const uint32_t SCR_WIDTH = 1600;
	const uint32_t SCR_HEIGHT = 1200;

	Game::Game()
	{
		m_VertexArray = std::make_shared<VertexArray>();

		float vertices[] = {
			// Position         // Tex Coords
		   -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
			0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		   -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		   -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		   -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		   -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		   -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		   -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
			0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		   -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		   -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		   -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
		};

		// Vertex Buffer
		std::shared_ptr m_VertexBuffer = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
		m_VertexBuffer->SetLayout({
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float2, "a_TexCoord"},
			});
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		uint32_t indices[] = {
			0, 1, 3,   // first triangle
			1, 2, 3    // second triangle
		};

		// Index Buffer
		std::shared_ptr m_IndexBuffer = std::make_unique<IndexBuffer>(indices, sizeof(indices));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		// Shader and Texture
		m_TestShader = std::make_shared<Shader>(VertexPath, FragmentPath);
		m_TestTexture = std::make_shared<Texture2D>(TexturePath);

		m_Camera = std::make_shared<Camera>(glm::vec3(0.0f, 0.0f, 3.0f));
	}

	void Game::OnAttach() {}
	void Game::OnDetach() {}

	void Game::OnUpdate(Timestep ts)
	{
		m_Camera->OnUpdate(ts);

		// Rendering
		glEnable(GL_DEPTH_TEST);
		glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Texture and Shader Binds
		m_TestTexture->Bind(0);
		m_TestShader->Bind();

		// Transformations
		glm::mat4 projection = glm::perspective(glm::radians(m_Camera->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		m_TestShader->SetMat4("u_Projection", projection);

		glm::mat4 view = m_Camera->GetViewMatrix();
		m_TestShader->SetMat4("u_View", view);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
		m_TestShader->SetMat4("u_Model", model);

		m_VertexArray->Bind();

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	void Game::OnEvent(Event& e)
	{
		m_Camera->OnEvent(e);
	}
}
