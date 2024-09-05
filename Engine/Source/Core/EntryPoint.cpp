#include <filesystem>
#include <iostream>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include "Core.h"
#include "Log.h"
#include "Renderer/Buffer.h"
#include "Renderer/Shader.h"
#include "Renderer/VertexArray.h"

const unsigned int SCR_WIDTH = 1600;
const unsigned int SCR_HEIGHT = 1200;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main()
{
    // Initialize GLFW with OpenGL 3.3
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    Quiet::Log::Init();

    // Create a Window
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Game", NULL, NULL);
    if (window == NULL)
    {
        LOG_ERROR("Failed to create GLFW window")
        glfwTerminate();
        return -1;
    }
	LOG_INFO("GLFW Window Success")
    glfwMakeContextCurrent(window);

    // Initialize Glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        LOG_ERROR("Failed to initialize GLAD")
        return -1;
    }
	LOG_INFO("Glad Load Success")
    

    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    float vertices[] = {
	     0.5f,  0.5f, 0.0f,  // top right
	     0.5f, -0.5f, 0.0f,  // bottom right
	    -0.5f, -0.5f, 0.0f,  // bottom left
	    -0.5f,  0.5f, 0.0f   // top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    // TEMP HARDCODED -
    std::string VertexPath = R"(D:\Code\Shooter_OpenGL\Engine\Assets\Shaders\TriangleVertexShader.glsl)";
    std::string FragmentPath = R"(D:\Code\Shooter_OpenGL\Engine\Assets\Shaders\TriangleFragShader.glsl)";

    Quiet::VertexArray VertexArray = Quiet::VertexArray();

    auto VertexBufferPtr = std::make_shared<Quiet::VertexBuffer>(vertices, sizeof(vertices));
    VertexBufferPtr->SetLayout({
        {Quiet::ShaderDataType::Float3, "a_Position"},
		});
    VertexArray.AddVertexBuffer(VertexBufferPtr);

    auto IndexBufferPtr = std::make_shared<Quiet::IndexBuffer>(indices, sizeof(indices));
    VertexArray.SetIndexBuffer(IndexBufferPtr);

    auto TriangleShader = std::make_shared<Quiet::Shader>(VertexPath, FragmentPath);

    glm::vec3 m_Color = { 0.8f, 0.8f, 0.4f };


    // Render Loop
    while (!glfwWindowShouldClose(window))
    {
        // Input
        processInput(window);

        // Rendering
        glClearColor(0.2f, 0.3f, 0.7f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        TriangleShader->Bind();
        TriangleShader->SetFloat3("u_Color", m_Color);

        VertexArray.Bind();
        IndexBufferPtr->Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        //glDrawArrays(GL_TRIANGLES, 0, 3);

        // Check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
