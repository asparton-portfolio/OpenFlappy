#pragma once

#include "../Shapes/Vector2D.h"
#include "../Shapes/Shape.h"

#include <GLM/glm.hpp>

class Renderer2D
{
public:
	explicit Renderer2D(const Vector2D<float>& windowSize);

	void clear() const;
	void draw(Shape& shape) const;

private:
	glm::mat4 m_projectionMatrix;
};

