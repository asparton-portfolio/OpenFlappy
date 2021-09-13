#include "ShaderProgram.h"

#include <iostream>

ShaderProgram::ShaderProgram(const Shader& vertexShader, const Shader& fragmentShader) : m_ID(0)
{
	// Shader program creation using the shader given in parameter
	m_ID = glCreateProgram();
	glAttachShader(m_ID, vertexShader.getID());
	glAttachShader(m_ID, fragmentShader.getID());
	glLinkProgram(m_ID);

	// The shaders are no more needed
	vertexShader.Destroy();
	fragmentShader.Destroy();
}

ShaderProgram::ShaderProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) : m_ID(0)
{
	// Shader creation
	Shader vertexShader(GL_VERTEX_SHADER, vertexShaderPath);
	Shader fragmentShader(GL_FRAGMENT_SHADER, fragmentShaderPath);

	// Shader program creation using the shader just created
	m_ID = glCreateProgram();
	glAttachShader(m_ID, vertexShader.getID());
	glAttachShader(m_ID, fragmentShader.getID());
	glLinkProgram(m_ID);

	// The shaders are no more needed
	vertexShader.Destroy();
	fragmentShader.Destroy();
}

void ShaderProgram::use() const
{
	glUseProgram(m_ID);
}

void ShaderProgram::unuse() const
{
	glUseProgram(0);
}

void ShaderProgram::SetUniform4f(const GLchar* name, const GLfloat& x, const GLfloat& y, const GLfloat& z, const GLfloat& w)
{
	GLint uniformLocation;
	std::map<const GLchar*, GLint>::iterator uniform = m_uniforms.find(name);
	if (uniform != m_uniforms.end())
	{
		uniformLocation = m_uniforms[name];
	}
	else
	{
		uniformLocation = glGetUniformLocation(m_ID, name);
		if (uniformLocation != -1)
			m_uniforms.insert(std::pair<const GLchar*, GLint>(name, uniformLocation));
	}

	glProgramUniform4f(m_ID, uniformLocation, x, y, z, w);
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(m_ID);
}