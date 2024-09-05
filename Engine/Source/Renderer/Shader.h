#pragma once

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

namespace Quiet
{
	enum ShaderType
	{
		VERTEX_SHADER,
		FRAGMENT_SHADER,
		GEOMETRY_SHADER,
		COMPUTE_SHADER,		// requires GL 4.3
		PROGRAM_SHADER
	};	

	class Shader
	{
	public:
		Shader(const std::string& vertexPath, const std::string& fragmentPath);
		~Shader();

		void Bind() const;
		void Unbind() const;

		void SetInt		(const std::string& name, int value);
		void SetIntArr	(const std::string& name, int* values, uint32_t count);
		void SetFloat	(const std::string& name, float value);
		void SetFloat2	(const std::string& name, const glm::vec2& values);
		void SetFloat3	(const std::string& name, const glm::vec3& values);
		void SetFloat4	(const std::string& name, const glm::vec4& values);
		void SetMat3	(const std::string& name, const glm::mat3& matrix);
		void SetMat4	(const std::string& name, const glm::mat4& matrix);

	private:
		uint32_t m_RendererID;
		std::string ReadFile(const std::string filepath);
		void CheckError(uint32_t shader, ShaderType type);
		void Compile(const std::unordered_map<ShaderType, std::string> shaderSources);
	};
}
