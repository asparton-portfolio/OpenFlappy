#pragma once

#include "Shape.h"

class Rectangle : public Shape
{
public:
	Rectangle(const Vector2D<float>& position, const Vector2D<float>& size);
	Rectangle(const Vector2D<float>& position, const Vector2D<float>& size, const Color& color);
	Rectangle(const Vector2D<float>& position, const Vector2D<float>& size, const Texture& texture);
	Rectangle(const Vector2D<float>& position, const Vector2D<float>& size, const Color& color, const Texture& texture);
	~Rectangle();

	// Setters
	void setSize(const Vector2D<float>& size);

	// Getters
	Vector2D<float> getSize() const;

private:
	// Specific to the shape
	Vector2D<float> m_size;



/// <summary>
/// FOR GRAPHIC REPRESENTATION
/// </summary>
public:
	void buildGraphicRepresentation(const glm::mat4& projectionMatrix) final;

private:
	void buildShaderProgram();
	void buildVertexBuffer();
};