#pragma once

#include "Shader.h"

#include <map>

class ShaderProgram
{
public:
	ShaderProgram(const Shader& vertexShader, const Shader& fragmentShader);
	ShaderProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	~ShaderProgram();

	void use() const;
	void unuse() const;

	void SetUniform4f(const GLchar* name, const GLfloat& x, const GLfloat& y, const GLfloat& z, const GLfloat& w);

private:
	GLuint m_ID;
	std::map<const GLchar*, GLint> m_uniforms;
};

