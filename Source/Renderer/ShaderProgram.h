#pragma once

#include "Shader.h"
#include "Color.h"

#include <map>
#include <GLM/glm.hpp>

/**
 * .Manage an opengl shader program.
 */
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
	void SetUniformColor(const GLchar* name, const Color& color);

private:
	GLint getUniformLocation(const GLchar* name);

	GLuint m_ID;
	std::map<const GLchar*, GLint> m_uniforms;	// Gather the shaders's uniforms
};

