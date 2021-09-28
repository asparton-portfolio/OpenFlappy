#include "Renderer2D.h"

#include "VertexArray.h"
#include "ShaderProgram.h"
#include "../Shapes/IShape.h"

#include <GLM/gtc/matrix_transform.hpp>

#include <iostream>

Renderer2D::Renderer2D(const Vector2D<float>& renderArea)
{
	m_projectionMatrix = glm::ortho(0.0f, renderArea.x, 0.0f, renderArea.y);
}

void Renderer2D::clear() const
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer2D::draw(IGraphicShape& graphicShape) const
{
	if (graphicShape.bufferVerticiesChanged())
		graphicShape.buildGraphicRepresentation(m_projectionMatrix);

	else if (graphicShape.shaderInfoChanged())
		graphicShape.updateShaders(m_projectionMatrix);

	graphicShape.getShaderProgram()->use();
	graphicShape.getVertexArray()->bind();

	if (graphicShape.getAssociatedShape()->getTexture())
		graphicShape.getAssociatedShape()->getTexture()->bind();

	glDrawElements(GL_TRIANGLES, graphicShape.getIndexBufferCount(), GL_UNSIGNED_INT, nullptr);
}