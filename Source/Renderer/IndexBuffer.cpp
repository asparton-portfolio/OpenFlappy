#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const GLuint data[], GLuint count) : m_ID(0), m_count(count)
{
	glCreateBuffers(1, &m_ID);
	bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
	unbind();
}

void IndexBuffer::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
}

void IndexBuffer::unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

unsigned int IndexBuffer::getCount() const
{
	return m_count;
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_ID);
}