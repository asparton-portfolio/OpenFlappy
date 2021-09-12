#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void bind() const;
	void unbind() const;

	void setVertexBufferLayout(const VertexBufferLayout& layout);
	void setVertexBufferLayout(const VertexBufferLayout& layout, const VertexBuffer& vertexBuffer);

private:
	GLuint m_ID;
};

