#pragma once

#include "IShape.h"

/**
 * .Represents a rectangle that has :
 *		- a position
 *		- a size
 *		- a color (white by default)
 *		- a texture (not mandatory)
 */
class Rectangle : public IShape
{
public:

	#pragma region Constructors using Vector2D

	Rectangle(const Vector2D<float>& position, const Vector2D<float>& size);
	Rectangle(const Vector2D<float>& position, const Vector2D<float>& size, const Color& color);
	Rectangle(const Vector2D<float>& position, const Vector2D<float>& size, Texture& texture);
	Rectangle(const Vector2D<float>& position, const Vector2D<float>& size, const Color& color, Texture& texture);

	#pragma endregion
	#pragma region Constructors using floats

	Rectangle(const float x, const float y, const float width, const float height);
	Rectangle(const float x, const float y, const float width, const float height, const Color& color);
	Rectangle(const float x, const float y, const float width, const float height, Texture& texture);
	Rectangle(const float x, const float y, const float width, const float height, const Color& color, Texture& texture);

	#pragma endregion
	~Rectangle() = default;

	/**
	 * .Determine wether the given rectangle is colliding with this rectangle.
	 *
	 * \param rectangle the other rectangle
	 * \return true if the given rectangle is colliding with this rectangle, false otherwise
	 */
	bool isColliding(const Rectangle& rectangle) const;

	// Setters
	void setPosition(const Vector2D<float>& position) final;
	void setPosition(const float x, const float y) final;
	void setSize(const Vector2D<float>& size) final;
	void setSize(const float width, const float height) final;

	void setColor(const Color& color) final;
	void setTexture(Texture& texture) final;

	// Getters
	Vector2D<float> getPosition() const final;
	Vector2D<float> getSize() const final;

	Color getColor() const final;
	Texture* getTexture() const final;

private:
	Vector2D<float> m_position;
	Vector2D<float> m_size;

	Color m_color;
	Texture* m_texture;
};