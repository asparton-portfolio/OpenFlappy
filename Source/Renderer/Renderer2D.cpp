#include "Renderer2D.h"

#include "ShaderProgram.h"

#include <GLM/gtc/matrix_transform.hpp>

#include <iostream>

Renderer2D::Renderer2D(const Vector2D<float>& windowSize)
{
	m_projectionMatrix = glm::ortho(0.0f, windowSize.x, 0.0f, windowSize.y);
}

void Renderer2D::clear() const
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer2D::draw(Shape& shape) const
{
	if (shape.verticiesChanged())
		shape.buildGraphicRepresentation(m_projectionMatrix);

	else if (shape.uniformChanged())
		shape.updateShaders(m_projectionMatrix);

	shape.getShaderProgram()->use();
	shape.getVertexArray()->bind();

	glDrawElements(GL_TRIANGLES, shape.getIndexBufferCount(), GL_UNSIGNED_INT, nullptr);
}