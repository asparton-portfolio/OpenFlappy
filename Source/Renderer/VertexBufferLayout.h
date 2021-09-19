#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <vector>

/**
 * .Gather informations about a layout element
 */
struct VertexBufferLayoutElement
{
	GLuint count;
	GLenum type;
	GLboolean normalized;
};

/**
 * .Represents the layout of a Vertex buffer to tell OpenGL how to interpret its data
 */
class VertexBufferLayout
{
public:
	VertexBufferLayout() = default;

	template <typename T>
	void Add(const unsigned int count)
	{
		// nothing
	}

	/**
	 * .Add a given number of floats to the layout
	 * 
	 * \param count the number of floats to add
	 */
	template<>
	void Add<GLfloat>(const unsigned int count)
	{
		VertexBufferLayoutElement element{ count, GL_FLOAT, GL_FALSE };
		m_elements.push_back(element);
		m_stride += count * sizeof(GLfloat);
	}

	inline std::vector<VertexBufferLayoutElement> getElements() const { return m_elements; }
	inline unsigned int getStride() const { return m_stride; }

private:
	std::vector<VertexBufferLayoutElement> m_elements;
	unsigned int m_stride;
};

