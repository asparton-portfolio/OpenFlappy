#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

/**
 * .Manage an opengl index buffer.
 */
class IndexBuffer
{
public:
	IndexBuffer() = default;
	explicit IndexBuffer(const GLuint data[], GLuint count);
	~IndexBuffer();

	void bind() const;
	void unbind() const;

	/**
	 * \return The number of indicies of the index buffer.
	 */
	unsigned int getCount() const;

private:
	GLuint m_ID;
	unsigned int m_count;
};

