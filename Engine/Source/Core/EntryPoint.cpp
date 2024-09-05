#include <filesystem>
#include <iostream>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include "Core.h"
#include "Log.h"
#include "Renderer/Buffer.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include "Renderer/VertexArray.h"

const unsigned int SCR_WIDTH = 1600;
const unsigned int SCR_HEIGHT = 1200;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main()
{
    // Initialize GLFW with OpenGL 3.3
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
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
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    // TEMP HARDCODED -
    std::string VertexPath = R"(D:\Code\Shooter_OpenGL\Engine\Assets\Shaders\VertexShader.glsl)";
    std::string FragmentPath = R"(D:\Code\Shooter_OpenGL\Engine\Assets\Shaders\FragShader.glsl)";
    std::string TexturePath = R"(D:\Code\Shooter_OpenGL\Engine\Assets\Textures\wall.jpg)";

    Quiet::VertexArray VertexArray = Quiet::VertexArray();

    auto VertexBufferPtr = std::make_shared<Quiet::VertexBuffer>(vertices, sizeof(vertices));
    VertexBufferPtr->SetLayout({
        {Quiet::ShaderDataType::Float3, "a_Position"},
		{Quiet::ShaderDataType::Float3, "a_Color"},
		{Quiet::ShaderDataType::Float2, "a_TexCoord"},
		});
    VertexArray.AddVertexBuffer(VertexBufferPtr);

    auto IndexBufferPtr = std::make_shared<Quiet::IndexBuffer>(indices, sizeof(indices));
    VertexArray.SetIndexBuffer(IndexBufferPtr);

    auto TestShader = std::make_shared<Quiet::Shader>(VertexPath, FragmentPath);
    auto TestTexture = std::make_shared<Quiet::Texture2D>(TexturePath);

    glm::vec3 m_Color = { 0.8f, 0.8f, 0.4f };

    // Render Loop
    while (!glfwWindowShouldClose(window))
    {
        // Input
        processInput(window);

        // Rendering
        glClearColor(0.2f, 0.3f, 0.7f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        TestShader->Bind();
        TestShader->SetFloat3("u_Color", m_Color);

        VertexArray.Bind();
        TestTexture->Bind();
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
