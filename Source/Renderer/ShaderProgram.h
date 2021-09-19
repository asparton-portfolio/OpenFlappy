#pragma once

#include "Shader.h"

#include <map>
#include <GLM/glm.hpp>

class ShaderProgram
{
public:
	ShaderProgram(const Shader& vertexShader, const Shader& fragmentShader);
	ShaderProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	~ShaderProgram();

	void use() const;
	void unuse() const;

	void SetUniform4f(const GLchar* name, const GLfloat& x, const GLfloat& y, const GLfloat& z, const GLfloat& w);
	void SetUniform1i(const GLchar* name, const GLint& value);
	void setUniformMat4(const GLchar* name, const glm::mat4& matrix);

private:
	GLint getUniformLocation(const GLchar* name);

	GLuint m_ID;
	std::map<const GLchar*, GLint> m_uniforms;
};

