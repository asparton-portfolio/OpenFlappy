#pragma once

#include "AGraphicShape.h"

#include "../Shapes/Rectangle.h"

/**
 * .Graphic representation of a rectangle
 */
class GraphicRectangle : public AGraphicShape
{
public:
	explicit GraphicRectangle(const Rectangle& rectangle);
	~GraphicRectangle();

	void checkUpdate() final;
	void buildGraphicRepresentation(const glm::mat4& projectionMatrix) final;
	void buildAndBindVertexBuffer() final;

private:
	Vector2D<float> m_size;	// the size of the rectangle

	void buildVertexBuffer() final;
};
