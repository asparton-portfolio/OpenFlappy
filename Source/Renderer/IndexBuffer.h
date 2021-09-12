#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

class IndexBuffer
{
public:
	explicit IndexBuffer(const GLuint data[], GLuint count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

private:
	GLuint m_ID;
};

