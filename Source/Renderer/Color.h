#pragma once

class Color
{
public:
	Color() :
		red(1.f), green(1.f), blue(1.f), alpha(1.f) {}

	Color(const float& red, const float& green, const float& blue) :
		red(red), green(green), blue(blue), alpha(1.0f) {}

	Color(const float& red, const float& green, const float& blue, const float& alpha) : 
		red(red), green(green), blue(blue), alpha(alpha) {}

	float red;
	float green;
	float blue;
	float alpha;
};