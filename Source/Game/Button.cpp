#include "Button.h"

Button::Button(const float x, const float y, const float width, const float height, Texture& texture, GLFWwindow* window) :
	Rectangle(x, y, width, height, texture), m_window(window) {}

Button::Button(const Vector2D<float> position, const Vector2D<float> size, Texture& texture, GLFWwindow* window) :
	Rectangle(position, size, texture), m_window(window) {}

bool Button::isPressed(int button) const
{
	Vector2D<double> currentMousePosition;
	glfwGetCursorPos(m_window, &currentMousePosition.x, &currentMousePosition.y);
	int state = glfwGetMouseButton(m_window, button);

	if (state == GLFW_PRESS &&
		currentMousePosition.x >= m_position.x &&
		currentMousePosition.x <= m_position.x + m_size.x &&
		currentMousePosition.y >= m_position.y &&
		currentMousePosition.y <= m_position.y + m_size.y)
		return true;

	return false;
}
