#pragma once

#include <string>
#include <unordered_map>

#include "glm/glm.hpp"


struct ShaderProgramSource {
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
private:
	std::string m_FilePath;
	unsigned int m_RendererID;
	std::unordered_map<std::string, int> m_UniformLocationCache;
public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	// Set Uniforms
	void SetUniforms1i(const std::string& name, int value);
	void SetUniforms1f(const std::string& name, float value);
	void SetUniforms4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniformsMat4f(const std::string& name, const glm::mat4& matrix);

private:
	unsigned int CompileShader(unsigned int shaderType, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	ShaderProgramSource ParseShader(const std::string& filepath);
	int GetUniformLocation(const std::string& name);
};