#pragma once

#include "IGraphicShape.h"
#include "../Shapes/Vector2D.h"

#include <GLM/glm.hpp>

/**
 * .Allow to render (draw) the graphic representation of a shape onto an area of the screen.
 */
class Renderer2D
{
public:
	explicit Renderer2D(const Vector2D<float>& renderArea);

	/**
	 * .Delete all the rendered pixels of the current opengl context.
	 */
	void clear() const;

	/**
	 * .Draw the graphic representation of a shape onto the render area.
	 * 
	 * \param graphicShape The graphic representation of a shape to draw.
	 */
	void draw(IGraphicShape& graphicShape) const;

private:
	glm::mat4 m_projectionMatrix;
};

