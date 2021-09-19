#include "Renderer/Renderer2D.h"
#include "Shapes/Rectangle.h"

#include <iostream>

#include <GLFW/glfw3.h>

int main()
{
	// Window & OpenGL context creation using GLFW
	if (glfwInit() != GLFW_TRUE)
		return -1;

	// OpenGL 4.5 version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(414, 736, "OpenFlappy", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	// GLEW initialisation
	if (glewInit() != GLEW_OK)
	{
		glfwDestroyWindow(window);
		glfwTerminate();
		return -1;
	}

	// Blending initialisation
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	/// RECTANGLE RENDERING

	Color bgColor(0.9f, 0.9f, 0.75f, 1.f);
	Vector2D<float> bgPosition(0.0f, 0.0f);
	Vector2D<float> bgSize(414.f, 736.f);
	Rectangle bg(bgPosition, bgSize, bgColor);
	
	Texture flappyTexture("Resources/Textures/flappyBird.png");
	Vector2D<float> flappyPosition(0.0f, 0.0f);
	Vector2D<float> flappySize(200.f, 200.f);
	Rectangle flappy(flappyPosition, flappySize, flappyTexture);

	Color flappyColor(0.1f, 0.14f, 0.4f, 0.2f);
	flappy.setColor(flappyColor);

	Vector2D<float> winSize(414.f, 736.f);
	Renderer2D renderer(winSize);

	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		// Set a background color
		renderer.clear();
		renderer.draw(bg);
		renderer.draw(flappy);

		glfwSwapBuffers(window);	// Swap between front and back buffers

		glfwPollEvents();	// Manage window events (like closing, resizing...)
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}