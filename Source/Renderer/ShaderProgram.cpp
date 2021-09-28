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

void ShaderProgram::SetUniform4f(const GLchar* name, const GLfloat& x, const GLfloat& y, const GLfloat& z, const GLfloat& w)
{
	GLint uniformLocation = getUniformLocation(name);
	if (uniformLocation != -1)
		glProgramUniform4f(m_ID, uniformLocation, x, y, z, w);
}

void ShaderProgram::SetUniform1i(const GLchar* name, const GLint& value)
{
	GLint uniformLocation = getUniformLocation(name);
	if (uniformLocation != -1)
		glProgramUniform1i(m_ID, uniformLocation, value);
}

void ShaderProgram::setUniformMat4(const GLchar* name, const glm::mat4& matrix)
{
	GLint uniformLocation = getUniformLocation(name);
	if (uniformLocation != -1)
		glProgramUniformMatrix4fv(m_ID, uniformLocation, 1, GL_FALSE, &matrix[0][0]);
}

void ShaderProgram::SetUniformColor(const GLchar* name, const Color& color)
{
	SetUniform4f(name, color.red, color.green, color.blue, color.alpha);
}

GLint ShaderProgram::getUniformLocation(const GLchar* name)
{
	std::map<const GLchar*, GLint>::iterator uniform = m_uniforms.find(name);
	if (uniform != m_uniforms.end())
	{
		return m_uniforms[name];
	}
	else
	{
		GLint uniformLocation = glGetUniformLocation(m_ID, name);

		if (uniformLocation != -1)
			m_uniforms.insert(std::pair<const GLchar*, GLint>(name, uniformLocation));

		return uniformLocation;
	}
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(m_ID);
}