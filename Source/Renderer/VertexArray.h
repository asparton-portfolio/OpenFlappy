#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

/**
 * .Manage an opengl vertex array.
 */
class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void bind() const;
	void unbind() const;

	/**
	 * .Bind the given layout to the last vertex buffer bound.
	 * 
	 * \param layout The vertex buffer layout to bind
	 */
	void setVertexBufferLayout(const VertexBufferLayout& layout) const;

	/**
	 * .Bind the given layout to the given vertex buffer.
	 *
	 * \param layout The vertex buffer layout to bind.
	 * \param vertexBuffer The vertex buffer to bind.
	 */
	void setVertexBufferLayout(const VertexBufferLayout& layout, const VertexBuffer& vertexBuffer) const;

private:
	GLuint m_ID;
};

