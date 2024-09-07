#include "Quiet_PCH.h"
#include "Application.h"

namespace Quiet
{
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
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		// Create a Window
		m_Window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, name.c_str(), NULL, NULL);
		if (m_Window == NULL)
		{
			QT_ASSERT(false, "Failed to create GLFW window")
			glfwTerminate();
		}
		glfwMakeContextCurrent(m_Window);
		glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			glViewport(0, 0, width, height);
		});
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xposIn, double yposIn)
		{
			float xpos = static_cast<float>(xposIn);
			float ypos = static_cast<float>(yposIn);

			if (firstMouse)
			{
				lastX = xpos;
				lastY = ypos;
				firstMouse = false;
			}

			float xoffset = xpos - lastX;
			float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

			lastX = xpos;
			lastY = ypos;
			m_Camera->MouseEvents(xoffset, yoffset);
		});
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset)
		{
			m_Camera->MouseWheelEvents(static_cast<float>(yoffset));
		});

		// tell GLFW to capture our mouse
		glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		// Initialize Glad
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			QT_ASSERT(false, "Failed to initialize GLAD")
		}

		glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

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

	void Application::Run()
	{
		// Render Loop
		while (!glfwWindowShouldClose(m_Window))
		{
			// Per-Frame DeltaTime
			float currentFrame = static_cast<float>(glfwGetTime());
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			// Input
			ProcessInput(m_Window);

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

			glfwSwapInterval(1);
			glfwSwapBuffers(m_Window);
			glfwPollEvents();
		}
	}

	void Application::Shutdown()
	{
		glfwTerminate();
	}

	void Application::ProcessInput(GLFWwindow* window)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			m_Camera->KeyboardEvents(FORWARD, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			m_Camera->KeyboardEvents(BACKWARD, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			m_Camera->KeyboardEvents(LEFT, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			m_Camera->KeyboardEvents(RIGHT, deltaTime);
	}
}
