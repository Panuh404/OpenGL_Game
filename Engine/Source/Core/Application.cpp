#include "Quiet_PCH.h"
#include "Application.h"

#include "Input.h"


namespace Quiet
{
	Application* Application::s_Instance = nullptr;

	// Settings
	const uint32_t SCR_WIDTH = 1600;
	const uint32_t SCR_HEIGHT = 1200;

	// Camera
	float lastX = SCR_WIDTH / 2.0f;
	float lastY = SCR_HEIGHT / 2.0f;
	bool firstMouse = true;

	// timing
	float deltaTime = 0.0f;	// time between current frame and last frame
	float lastFrame = 0.0f;

	std::shared_ptr<Camera> m_Camera;

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
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	Application::Application(const std::string& name)
	{
		s_Instance = this;
		WindowProps props = {
			"Test",
			1600,
			1200,
		};
		m_Window = std::make_unique<Window>(props);
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		m_TestShader = std::make_shared<Shader>(VertexPath, FragmentPath);
		m_TestTexture = std::make_shared<Texture2D>(TexturePath);

		m_VertexArray = std::make_shared<VertexArray>();

		m_VertexBuffer = std::make_shared<VertexBuffer>(vertices, sizeof(vertices));
		m_VertexBuffer->SetLayout({
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float2, "a_TexCoord"},
			});
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		m_IndexBuffer = std::make_shared<IndexBuffer>(indices, sizeof(indices));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);
		m_Camera = std::make_shared<Camera>(glm::vec3(0.0f, 0.0f, 3.0f));
	}

	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize));

		m_Camera->OnEvent(event);
	}

	void Application::Run()
	{
		// Render Loop
		while (m_Running)
		{
			// Per-Frame DeltaTime
			float currentFrame = static_cast<float>(glfwGetTime());
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			// Input
			m_Camera->OnUpdate(deltaTime);
			if (Input::IsKeyPressed(Key::Escape))
			{
				m_Running = false;
			}

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
			m_IndexBuffer->Bind();

			glDrawArrays(GL_TRIANGLES, 0, 36);

			m_Window->SetVSync(true);
			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& event)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& event)
	{
		glViewport(0, 0, event.GetWidth(), event.GetHeight());
		return false;
	}
}
