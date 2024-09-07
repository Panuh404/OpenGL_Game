#include "Quiet_PCH.h"
#include "Shader.h"

#include <glad/glad.h>
#include <fstream>

#include "glm/gtc/type_ptr.hpp"

namespace Quiet
{
	Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
	{
		std::unordered_map<ShaderType, std::string> sources;
		sources[VERTEX_SHADER] = ReadFile(vertexPath);
		sources[FRAGMENT_SHADER] = ReadFile(fragmentPath);
		Compile(sources);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_RendererID);
	}

	void Shader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void Shader::Unbind() const
	{
		glUseProgram(0);
	}

	

	std::string Shader::ReadFile(const std::string filepath)
	{
		std::string result;
		std::ifstream input(filepath, std::ios::in | std::ios::binary);
		if (input)
		{
			input.seekg(0, std::ios::end);
			size_t size = input.tellg();
			if (size != -1)
			{
				result.resize(size);
				input.seekg(0, std::ios::beg);
				input.read(&result[0], size);
				input.close();
			}
			else
			{
				LOG_ERROR("COULD NOT READ FROM FILE '{0}'", filepath)
			}
		}
		else
		{
			LOG_ERROR("COULD NOT OPEN FILE '{0}'", filepath)
		}
		return result;
	}

	void Shader::CheckError(uint32_t shader, ShaderType type)
	{
		int success;
		char infoLog[1024];
		if (type == VERTEX_SHADER)
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				LOG_ERROR("SHADER COMPILATION ERROR::VERTEX\n {0}", infoLog)
			}
		}
		if (type == FRAGMENT_SHADER)
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				LOG_ERROR("SHADER COMPILATION ERROR::FRAGMENT\n {0}", infoLog)
			}
		}
		if (type == PROGRAM_SHADER)
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				LOG_ERROR("SHADER LINKING ERROR\n {0}", infoLog)
			}
		}
	}

	void Shader::Compile(const std::unordered_map<ShaderType, std::string> Sources)
	{
		m_RendererID = glCreateProgram(); // Create the shader program

		// Vertex Shader
		uint32_t VertexShader = glCreateShader(GL_VERTEX_SHADER);
		const char* VertexSource = Sources.find(VERTEX_SHADER)->second.c_str();
		glShaderSource(VertexShader, 1, &VertexSource, nullptr);
		glCompileShader(VertexShader);
		CheckError(VertexShader, VERTEX_SHADER);

		// Fragment Shader
		uint32_t FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		const char* FragmentSource = Sources.find(FRAGMENT_SHADER)->second.c_str();
		glShaderSource(FragmentShader, 1, &FragmentSource, nullptr);
		glCompileShader(FragmentShader);
		CheckError(FragmentShader, FRAGMENT_SHADER);

		// Attach shaders to the program
		glAttachShader(m_RendererID, VertexShader);
		glAttachShader(m_RendererID, FragmentShader);

		// Link the program
		glLinkProgram(m_RendererID);
		CheckError(m_RendererID, PROGRAM_SHADER);

		// Cleanup
		glDeleteShader(VertexShader);
		glDeleteShader(FragmentShader);
	}

	void Shader::SetInt(const std::string& name, int value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(location, value);
	}

	void Shader::SetIntArr(const std::string& name, int* values, uint32_t count)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1iv(location, count, values);
	}

	void Shader::SetFloat(const std::string& name, float value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1f(location, value);
	}

	void Shader::SetFloat2(const std::string& name, const glm::vec2& values)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2f(location, values.x, values.y);
	}

	void Shader::SetFloat3(const std::string& name, const glm::vec3& values)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3f(location, values.x, values.y, values.z);
	}

	void Shader::SetFloat4(const std::string& name, const glm::vec4& values)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4f(location, values.x, values.y, values.z, values.w);
	}

	void Shader::SetMat3(const std::string& name, const glm::mat3& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void Shader::SetMat4(const std::string& name, const glm::mat4& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
}
