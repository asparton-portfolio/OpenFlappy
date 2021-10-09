#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../Shapes/Rectangle.h"

/**
 * .A rectangle that can detect if a mouse click happened inside itself.
 */
class Button : public Rectangle {

public:
	Button(const float x, const float y, const float width, const float height, Texture& texture, GLFWwindow* window);
	Button(const Vector2D<float> position, const Vector2D<float> size, Texture& texture, GLFWwindow* window);
	~Button() = default;

	/**
	 * .Determine if the given mouse button is pressed inside the rectangle.
	 * 
	 * \param button the mouse button (left, right...)
	 * \return true if the given mouse button is pressed inside the rectangle, false otherwise.
	 */
	bool isPressed(int button) const;

private:
	GLFWwindow* m_window;	// Need window to listen to mouse inputs
};