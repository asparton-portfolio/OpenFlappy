#include "Rectangle.h"

#include <iostream>
#include <string>

Rectangle::Rectangle(const Vector2D<float>& position, const Vector2D<float>& size) :
	Shape(position), m_size(size) 
{
	// Index buffer initialisation (done only one beacause it never changes)
	GLuint m_indicies[6] = { 0, 1, 2, 3, 0, 2 };
	m_indexBuffer = new IndexBuffer(m_indicies, 6);
}

Rectangle::Rectangle(const Vector2D<float>& position, const Vector2D<float>& size, const Color& color) :
	Shape(position, color), m_size(size)
{
	// Index buffer initialisation (done only one beacause it never changes)
	GLuint m_indicies[6] = { 0, 1, 2, 3, 0, 2 };
	m_indexBuffer = new IndexBuffer(m_indicies, 6);
}

Rectangle::Rectangle(const Vector2D<float>& position, const Vector2D<float>& size, const Texture& texture) :
	Shape(position, texture), m_size(size) 
{
	// Index buffer initialisation (done only one beacause it never changes)
	GLuint m_indicies[6] = { 0, 1, 2, 3, 0, 2 };
	m_indexBuffer = new IndexBuffer(m_indicies, 6);
}

Rectangle::Rectangle(const Vector2D<float>& position, const Vector2D<float>& size, const Color& color, const Texture& texture) :
	Shape(position, color, texture), m_size(size) 
{
	// Index buffer initialisation (done only one beacause it never changes)
	GLuint m_indicies[6] = { 0, 1, 2, 3, 0, 2 };
	m_indexBuffer = new IndexBuffer(m_indicies, 6);
}

void Rectangle::setSize(const Vector2D<float>& size)
{
	if (m_size != size)
		m_size = size;
}

Vector2D<float> Rectangle::getSize() const
{
	return m_size;
}

//
// For graphic representation
//

void Rectangle::buildGraphicRepresentation(const glm::mat4& projectionMatrix)
{
	buildShaderProgram();
	updateShaders(projectionMatrix);

	if (m_vertexArray)
		delete m_vertexArray;
	m_vertexArray = new VertexArray();
	m_vertexArray->bind();

	buildVertexBuffer();
	m_vertexBuffer->bind();
	m_vertexArray->setVertexBufferLayout(*m_vertexBufferLayout, *m_vertexBuffer);

	m_indexBuffer->bind();

	m_shaderProgram->unuse();
	m_vertexArray->unbind();
	m_vertexBuffer->unbind();
	m_indexBuffer->unbind();

	m_verticiesChanged = false;
}

void Rectangle::buildShaderProgram()
{
	std::string shaderName = "Color";
	if (m_texture)
		shaderName = "Texture";

	m_shaderProgram = new ShaderProgram("Resources/Shaders/" + shaderName + "Vertex.shader", "Resources/Shaders/" + shaderName + "Fragment.shader");
}

void Rectangle::buildVertexBuffer()
{
	// If there is an existing buffer, we clear the memory first before pointing to a new one
	if (m_vertexBuffer)
		delete m_vertexBuffer;

	if (m_vertexBufferLayout)
		delete m_vertexBufferLayout;
	m_vertexBufferLayout = new VertexBufferLayout();

	if (m_texture)
	{
		GLfloat verticies[16] = {
					  1.f, 1.f,		0.0f, 0.0f,
				 m_size.x, 1.f,		1.0f, 0.0f,
			m_size.x, m_size.y,		1.0f, 1.0f,
				 1.f, m_size.y,		0.0f, 1.0f
		};
		m_vertexBuffer = new VertexBuffer(verticies, 16 * sizeof(GLfloat));

		// Two floats more for the texture
		m_vertexBufferLayout->Add<GLfloat>(2);
	}
	else
	{
		GLfloat verticies[8] = {
					  0.f, 0.f,
				 m_size.x, 0.f,
			m_size.x, m_size.y,
				 0.f, m_size.y
		};
		m_vertexBuffer = new VertexBuffer(verticies, 8 * sizeof(GLfloat));
	}

	m_vertexBufferLayout->Add<GLfloat>(2);
}




Rectangle::~Rectangle()
{	
	delete m_vertexArray;
	delete m_vertexBuffer;
	delete m_vertexBufferLayout;	
	delete m_indexBuffer;
	delete m_shaderProgram;
	delete m_texture;
}