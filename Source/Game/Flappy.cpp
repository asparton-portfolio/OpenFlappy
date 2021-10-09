#include "Flappy.h"


Flappy::Flappy(const float x, const float y, const float width, const float height, Texture& texture, GLFWwindow* window, 
	const AnchorPointLocation location, const float weight) :
	Rectangle(x, y, width, height, texture, location), m_window(window), m_weight(weight), m_firstJumpDone(false), m_nextJumpHeight(-1), 
	m_jumpAccelerationFactor(), m_gravityAccelerationFactor(15.f), m_jumpHeightEdgeCount()
{
	// Bind keyboard input listening to my function
	glfwSetKeyCallback(m_window, &onKeyPressed);
	glfwSetWindowUserPointer(m_window, this);
}

Flappy::Flappy(const Vector2D<float> position, const Vector2D<float> size, Texture& texture, GLFWwindow* window, 
	const AnchorPointLocation location, const float weight) :
	Rectangle(position, size, texture, location), m_window(window), m_weight(weight), m_firstJumpDone(false), m_nextJumpHeight(-1), 
	m_jumpAccelerationFactor(), m_gravityAccelerationFactor(15.f), m_jumpHeightEdgeCount()
{
	// Bind keyboard input listening to my function
	glfwSetKeyCallback(m_window, &onKeyPressed);
	glfwSetWindowUserPointer(m_window, this);
}

Rectangle Flappy::getCollisionBox() const
{
	Rectangle collisionBox(m_position.x + m_size.x / 3, m_position.y + m_size.y / 3, m_size.x / 3, m_size.y / 3);
	return collisionBox;
}

void Flappy::applyGravity(const bool jumpHeightReached)
{
	// To make flappy slightly go up before falling
	if (jumpHeightReached)
	{
		m_gravityAccelerationFactor = 15.f;
		m_jumpHeightEdgeCount = 1;
	}

	if (m_jumpHeightEdgeCount > 0 && m_jumpHeightEdgeCount < 10)
	{
		setPosition(m_position.x, m_position.y + 0.5f);	// Tiny movement going up
		m_jumpHeightEdgeCount++;
	}
	else if (m_jumpHeightEdgeCount == 10)
		m_jumpHeightEdgeCount = -1;
	else
		setPosition(m_position.x, m_position.y - m_weight / m_gravityAccelerationFactor);

	if (m_gravityAccelerationFactor > 1 && m_jumpHeightEdgeCount == -1)
		m_gravityAccelerationFactor -= 1.f;

	if (m_rotation >= -90.f && m_jumpHeightEdgeCount == -1)
		m_rotation -= 3.f;
}

void Flappy::jump()
{
	if (m_jumpAccelerationFactor == 0 && m_nextJumpHeight < 0.f)
	{
		m_nextJumpHeight = m_position.y + (float)Flappy::JUMP_HEIGHT;
		m_jumpAccelerationFactor = 5;
	}
		
	if (m_position.y < m_nextJumpHeight)
	{
		setPosition(m_position.x, m_position.y + (float)Flappy::JUMP_HEIGHT / (float)m_jumpAccelerationFactor);
		m_jumpAccelerationFactor += 1;
	}
	else
	{
		m_jumpAccelerationFactor = 0;
		m_nextJumpHeight = -1.f;
	}

	if (!m_firstJumpDone)
		m_firstJumpDone = true;
}

bool Flappy::isJumping() const
{
	return m_jumpAccelerationFactor > 0;
}

void Flappy::resetFirstJumpDone()
{
	m_firstJumpDone = false;
	m_jumpAccelerationFactor = 0;
}

bool Flappy::firstJumpDone() const
{
	return m_firstJumpDone;
}

void onKeyPressed(GLFWwindow* window, int key, [[maybe_unused]] int scancode, int action, [[maybe_unused]] int mods)
{
	Flappy* flappy = (Flappy*)glfwGetWindowUserPointer(window);

	if (action == GLFW_PRESS && key == GLFW_KEY_SPACE)
		flappy->jump();
}