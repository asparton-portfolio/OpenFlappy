#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <string>

/**
 * .Allow to create a shader from a file.
 */
class Shader
{
public:
	Shader(const GLenum& shaderType, const std::string& pathToShader);
	void Destroy() const;

	GLuint getID() const;

private:
	GLuint m_ID;
	std::string m_pathToShader;

	/**
	 * .Recover the source code of the given file.
	 * 
	 * \param path the path to the shader source
	 * \return the source code
	 */
	static std::string getSourceCode(const std::string& path);
};

