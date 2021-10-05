#include "GraphicRectangle.h"

GraphicRectangle::GraphicRectangle(const Rectangle& rectangle) : AGraphicShape((IShape*)&rectangle), m_size(m_shape->getSize())
{
	const GLuint indicies[6] = { 0, 1, 2, 3, 0, 2 };
	m_indexBuffer = new IndexBuffer(indicies, 6);
}

void GraphicRectangle::checkUpdate()
{
	AGraphicShape::checkUpdate();

	if (m_shape->getSize() != m_size)
	{
		m_size = m_shape->getSize();

		m_bufferVerticiesChanged = true;
		m_colorChanged = true;
		m_positionChanged = true;
		if (m_texture)
			m_textureChanged = true;
	}
}

void GraphicRectangle::buildGraphicRepresentation(const glm::mat4& projectionMatrix)
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

	m_bufferVerticiesChanged = false;
}

void GraphicRectangle::buildAndBindVertexBuffer()
{
	m_vertexArray->bind();
	buildVertexBuffer();
	m_vertexBuffer->bind();
	m_vertexArray->setVertexBufferLayout(*m_vertexBufferLayout, *m_vertexBuffer);

	m_vertexArray->unbind();
	m_vertexBuffer->unbind();
	m_bufferVerticiesChanged = false;
}

void GraphicRectangle::buildVertexBuffer()
{
	// If there is an existing buffer, we clear the memory first before pointing to a new one
	if (m_vertexBuffer)
		delete m_vertexBuffer;

	if (m_vertexBufferLayout)
		delete m_vertexBufferLayout;
	m_vertexBufferLayout = new VertexBufferLayout();

	Vector2D<float> bottomLeftCorner = AGraphicShape::getPositionByRotation(0.f, 0.f, m_rotation);
	Vector2D<float> bottomRightCorner = AGraphicShape::getPositionByRotation(m_shape->getSize().x, 0.f, m_rotation);
	Vector2D<float> topRightCorner = AGraphicShape::getPositionByRotation(m_shape->getSize().x, m_shape->getSize().y, m_rotation);
	Vector2D<float> topLeftCorner = AGraphicShape::getPositionByRotation(0.f, m_shape->getSize().y, m_rotation);

	if (m_shape->getTexture())
	{
		GLfloat verticies[16] = {
			bottomLeftCorner.x, bottomLeftCorner.y,		0.f, 0.f,
			bottomRightCorner.x, bottomRightCorner.y,	1.f, 0.f,
			topRightCorner.x, topRightCorner.y,			1.f, 1.f,
			topLeftCorner.x, topLeftCorner.y,			0.f, 1.f
		};
		m_vertexBuffer = new VertexBuffer(verticies, 16 * sizeof(GLfloat));

		// Two floats more for the texture
		m_vertexBufferLayout->Add<GLfloat>(2);
	}
	else
	{
		GLfloat verticies[8] = {
			bottomLeftCorner.x, bottomLeftCorner.y,
			bottomRightCorner.x, bottomRightCorner.y,
			topRightCorner.x, topRightCorner.y,
			topLeftCorner.x, topLeftCorner.y,
		};
		m_vertexBuffer = new VertexBuffer(verticies, 8 * sizeof(GLfloat));
	}

	m_vertexBufferLayout->Add<GLfloat>(2);
}


GraphicRectangle::~GraphicRectangle()
{
	delete m_shaderProgram;
	delete m_vertexArray;
	delete m_vertexBuffer;
	delete m_vertexBufferLayout;
	delete m_indexBuffer;
	
	// Don't need to delete the pointer to the shape because the memory is not allocated
}