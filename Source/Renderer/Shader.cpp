#include "Shader.h"

#include <iostream>
#include <fstream>

Shader::Shader(const GLenum& shaderType, const std::string& pathToShader) : m_ID(0), m_pathToShader(pathToShader)
{
	if (shaderType == GL_VERTEX_SHADER || shaderType == GL_FRAGMENT_SHADER)
	{
		m_ID = glCreateShader(shaderType);

		const std::string stringSrcCode = Shader::getSourceCode(m_pathToShader);
		const GLchar* srcCode = stringSrcCode.c_str();
		glShaderSource(m_ID, 1, &srcCode, nullptr);
		glCompileShader(m_ID);
	}
	else
	{
		std::cout << "ERROR: SHADER TYPE NOT SUPPORTED." << std::endl;
	}
}

void Shader::Destroy() const
{
	glDeleteShader(m_ID);
}

GLuint Shader::getID() const
{
	return m_ID;
}

std::string Shader::getSourceCode(const std::string& path)
{
	std::ifstream fileStream(path);

	if (!fileStream)
	{
		std::cout << "ERROR: FILE NOT FOUND." << std::endl;
		return std::string();
	}

	std::string srcCode = "";
	std::string line;
	while (std::getline(fileStream, line))
	{
		srcCode += line + "\n";
	}
	return srcCode;
}
