#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

class IndexBuffer
{
public:
	IndexBuffer() = default;
	explicit IndexBuffer(const GLuint data[], GLuint count);
	~IndexBuffer();

	void bind() const;
	void unbind() const;

private:
	GLuint m_ID;
};

