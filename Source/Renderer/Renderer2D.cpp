#include "Renderer2D.h"

#include "ShaderProgram.h"

#include <GLM/gtc/matrix_transform.hpp>

Renderer2D::Renderer2D(const Vector2D<float>& windowSize)
{
	m_projectionMatrix = glm::ortho(0.0f, windowSize.x, 0.0f, windowSize.y);
}

void Renderer2D::clear() const
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer2D::draw(const Rectangle& rectangle) const
{
	rectangle.getShaderProgram()->use();
	rectangle.getShaderProgram()->setUniformMat4("u_MVP", m_projectionMatrix);

	rectangle.getVertexArray()->bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}