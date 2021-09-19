#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

class Texture
{
public:
	explicit Texture(const char* texturePath);
	~Texture();

	void bind(const int samplerSlot = 0);
	void unbind() const;

	GLint getSamplerSlot() const;
	const char* getPath() const;

private:
	GLuint m_ID;
	GLint m_samplerSlot;

	const char* m_path;
};

