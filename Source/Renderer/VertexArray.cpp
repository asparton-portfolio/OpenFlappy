#include "VertexArray.h"

VertexArray::VertexArray() : m_ID(0)
{
	glCreateVertexArrays(1, &m_ID);
}

void VertexArray::bind() const
{
	glBindVertexArray(m_ID);
}

void VertexArray::unbind() const
{
	glBindVertexArray(0);
}

void VertexArray::setVertexBufferLayout(const VertexBufferLayout& layout) const
{
	unsigned int offset = 0;
	for (int i = 0; i < layout.getElements().size(); i++)
	{
		VertexBufferLayoutElement element = layout.getElements()[i];
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const GLvoid*)offset);
		glEnableVertexAttribArray(i);
		offset += element.count * sizeof(element.type);
	}}

void VertexArray::setVertexBufferLayout(const VertexBufferLayout& layout, const VertexBuffer& vertexBuffer) const
{
	vertexBuffer.bind();
	setVertexBufferLayout(layout);
	vertexBuffer.unbind();
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_ID);
}