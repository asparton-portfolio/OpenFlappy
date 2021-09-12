#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

class VertexBuffer
{
public:
	explicit VertexBuffer(const GLvoid* data, GLsizei size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

private:
	GLuint m_ID;
};

