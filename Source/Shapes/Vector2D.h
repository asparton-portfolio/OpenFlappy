#pragma once

template <typename T>
class Vector2D
{
public:
	T x;
	T y;

	Vector2D(const T& x, const T& y) : x(x), y(y) {}
};

template <typename T>
bool operator==(const Vector2D<T>& position1, const Vector2D<T>& position2)
{
	return position1.x == position2.x && position1.y == position2.y;
}

template <typename T>
bool operator!=(const Vector2D<T>& position1, const Vector2D<T>& position2)
{
	return !(position1 == position2);
}