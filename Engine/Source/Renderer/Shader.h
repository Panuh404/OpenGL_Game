#pragma once

#include <string>
#include <unordered_map>

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

	private:
		uint32_t m_RendererID;
		std::string ReadFile(const std::string filepath);
		void CheckError(uint32_t shader, ShaderType type);
		void Compile(const std::unordered_map<ShaderType, std::string> shaderSources);
	};
}
