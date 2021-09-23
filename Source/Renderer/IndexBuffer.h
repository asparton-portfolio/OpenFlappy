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

	unsigned int getCount() const;

private:
	GLuint m_ID;
	unsigned int m_count;
};

