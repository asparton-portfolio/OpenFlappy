#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const GLuint data[], GLuint count) : m_ID(0)
{
	glCreateBuffers(1, &m_ID);
	Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
	Unbind();
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
}

void IndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_ID);
}