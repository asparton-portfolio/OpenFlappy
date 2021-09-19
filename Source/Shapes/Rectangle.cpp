#include "Rectangle.h"

#include <iostream>
#include <string>

Rectangle::Rectangle(const Vector2D<float>& position, const Vector2D<float>& size) :
	m_position(position), m_size(size), m_color(new Color())
{
	build();
}

Rectangle::Rectangle(const Vector2D<float>& position, const Vector2D<float>& size, const Color& color) :
	m_position(position), m_size(size), m_color(new Color(color))
{
	build();
}

Rectangle::Rectangle(const Vector2D<float>& position, const Vector2D<float>& size, const Texture& texture) :
	m_position(position), m_size(size), m_color(new Color()), m_texture(new Texture(texture.getPath()))
{
	build();
}

Rectangle::Rectangle(const Vector2D<float>& position, const Vector2D<float>& size, const Color& color, const Texture& texture) :
	m_position(position), m_size(size), m_color(new Color(color)), m_texture(new Texture(texture.getPath()))
{
	build();
}

void Rectangle::build()
{
	buildShaderProgram();
	m_shaderProgram->use();
	m_shaderProgram->SetUniform4f("u_Color", m_color->red, m_color->green, m_color->blue, m_color->alpha);

	if (m_texture)
	{
		m_texture->bind();
		m_shaderProgram->SetUniform1i("u_Texture", m_texture->getSamplerSlot());
	}

	m_vertexArray = new VertexArray();
	m_vertexArray->bind();

	buildVertexBuffer();
	m_vertexBuffer->bind();
	m_vertexArray->setVertexBufferLayout(*m_vertexBufferLayout, *m_vertexBuffer);

	// Index buffer initialisation
	GLuint m_indicies[6] = { 0, 1, 2, 3, 0, 2 };
	m_indexBuffer = new IndexBuffer(m_indicies, 6);
	m_indexBuffer->bind();

	m_shaderProgram->unuse();
	m_vertexArray->unbind();
	m_vertexBuffer->unbind();
	m_indexBuffer->unbind();
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
	m_vertexBufferLayout = new VertexBufferLayout();

	if (m_texture)
	{
		GLfloat verticies[16] = {
			m_position.x,			 m_position.y,			  0.0f, 0.0f,
			m_position.x + m_size.x, m_position.y,			  1.0f, 0.0f,
			m_position.x + m_size.x, m_position.y + m_size.y, 1.0f, 1.0f,
			m_position.x,			 m_position.y + m_size.y, 0.0f, 1.0f
		};
		m_vertexBuffer = new VertexBuffer(verticies, 16 * sizeof(GLfloat));
		
		// Two floats more for the texture
		m_vertexBufferLayout->Add<GLfloat>(2);
	}
	else
	{
		GLfloat verticies[8] = {
			m_position.x,			 m_position.y,
			m_position.x + m_size.x, m_position.y,
			m_position.x + m_size.x, m_position.y + m_size.y,
			m_position.x,			 m_position.y + m_size.y
		};
		m_vertexBuffer = new VertexBuffer(verticies, 8 * sizeof(GLfloat));
	}

	m_vertexBufferLayout->Add<GLfloat>(2);
}

void Rectangle::setPosition(const Vector2D<float>& position)
{
	if (m_position != position)
	{
		m_position = position;
		build();
	}
}

void Rectangle::setSize(const Vector2D<float>& size)
{
	if (m_size != size)
	{
		m_size = size;
		build();
	}
}

void Rectangle::setColor(const Color& color)
{
	if (m_color)
		delete m_color;

	m_color = new Color(color);
	m_shaderProgram->use();
	m_shaderProgram->SetUniform4f("u_Color", m_color->red, m_color->green, m_color->blue, m_color->alpha);
	m_shaderProgram->unuse();
}

void Rectangle::setTexture(const Texture& texture)
{
	if (m_texture)
		delete m_texture;

	m_texture = new Texture(texture.getPath());
	m_texture->bind();
	m_shaderProgram->use();
	m_shaderProgram->SetUniform1i("u_Texture", m_texture->getSamplerSlot());
	m_shaderProgram->unuse();
}

Vector2D<float> Rectangle::getPosition() const
{
	return m_position;
}

Vector2D<float> Rectangle::getSize() const
{
	return m_size;
}

Color* Rectangle::getColor() const
{
	return m_color;
}

ShaderProgram* Rectangle::getShaderProgram() const
{
	return m_shaderProgram;
}

VertexArray* Rectangle::getVertexArray() const
{
	return m_vertexArray;
}

Rectangle::~Rectangle()
{	
	delete m_vertexArray;
	m_vertexArray = nullptr;
	
	delete m_vertexBuffer;
	m_vertexBuffer = nullptr;

	delete m_vertexBufferLayout;
	m_vertexBufferLayout = nullptr;
	
	delete m_indexBuffer;
	m_indexBuffer = nullptr;
	
	delete m_shaderProgram;
	m_shaderProgram = nullptr;
}