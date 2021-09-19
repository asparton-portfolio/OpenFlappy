#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

class VertexBuffer
{
public:
	VertexBuffer() = default;
	explicit VertexBuffer(const GLvoid* data, GLsizei size);
	~VertexBuffer();

	void bind() const;
	void unbind() const;

private:
	GLuint m_ID;
};

