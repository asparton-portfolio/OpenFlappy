#include "Rectangle.h"

#pragma region Constructors

Rectangle::Rectangle(const Vector2D<float>& position, const Vector2D<float>& size) :
	m_position(position), m_size(size), m_color(), m_texture(nullptr) {}

Rectangle::Rectangle(const Vector2D<float>& position, const Vector2D<float>& size, const Color& color) :
	m_position(position), m_size(size), m_color(color), m_texture(nullptr) {}

Rectangle::Rectangle(const Vector2D<float>& position, const Vector2D<float>& size, Texture& texture) :
	m_position(position), m_size(size), m_color(), m_texture(&texture) {}

Rectangle::Rectangle(const Vector2D<float>& position, const Vector2D<float>& size, const Color& color, Texture& texture) :
	m_position(position), m_size(size), m_color(color), m_texture(&texture) {}

Rectangle::Rectangle(const float x, const float y, const float width, const float height) :
	m_position(x, y), m_size(width, height), m_color(), m_texture(nullptr) {}

Rectangle::Rectangle(const float x, const float y, const float width, const float height, const Color& color) :
	m_position(x, y), m_size(width, height), m_color(color), m_texture(nullptr) {}

Rectangle::Rectangle(const float x, const float y, const float width, const float height, Texture& texture) :
	m_position(x, y), m_size(width, height), m_color(), m_texture(&texture) {}

Rectangle::Rectangle(const float x, const float y, const float width, const float height, const Color& color, Texture& texture) :
	m_position(x, y), m_size(width, height), m_color(color), m_texture(&texture) {}

#pragma endregion

bool Rectangle::isColliding(const Rectangle& rectangle) const
{
	return rectangle.getPosition().x + rectangle.getSize().x >= m_position.x && rectangle.getPosition().x <= m_position.x + m_size.x &&
		   rectangle.getPosition().y + rectangle.getSize().y >= m_position.y && rectangle.getPosition().y <= m_position.y + m_size.y;
}

/// <summary>
/// SETTERS
/// </summary>

void Rectangle::setPosition(const Vector2D<float>& position)
{
	m_position = position;
}

void Rectangle::setPosition(const float x, const float y)
{
	m_position.y = y;
	m_position.x = x;
}

void Rectangle::setSize(const Vector2D<float>& size)
{
	m_size = size;
}

void Rectangle::setSize(const float width, const float height)
{
	m_size.x = width;
	m_size.y = height;
}

void Rectangle::setColor(const Color& color)
{
	m_color = color;
}

void Rectangle::setTexture(Texture& texture)
{
	m_texture = &texture;
}


/// <summary>
/// GETTERS
/// </summary>

Vector2D<float> Rectangle::getPosition() const
{
	return m_position;
}

Vector2D<float> Rectangle::getSize() const
{
	return m_size;
}

Color Rectangle::getColor() const
{
	return m_color;
}

Texture* Rectangle::getTexture() const
{
	return m_texture;
}