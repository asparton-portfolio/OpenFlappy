#include "ShaderProgram.h"

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

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(m_ID);
}