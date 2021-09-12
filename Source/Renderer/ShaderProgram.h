#pragma once

#include "Shader.h"

class ShaderProgram
{
public:
	ShaderProgram(const Shader& vertexShader, const Shader& fragmentShader);
	ShaderProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	~ShaderProgram();

	void Use() const;
	void Unuse() const;

private:
	GLuint m_ID;
};

