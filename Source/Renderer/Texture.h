#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

/**
 * .Manage an opengl texture using STB.
 */
class Texture
{
public:
	explicit Texture(const char* texturePath, const GLint samplerSlot = 0, const bool flipVertically = true);
	~Texture();

	void bind() const;
	void unbind() const;

	GLuint getSamplerSlot() const;
	const char* getPath() const;
	bool isFlipped() const;

private:
	GLuint m_ID;
	GLuint m_samplerSlot;
	const bool m_isFlipped;

	const char* m_path;
};

