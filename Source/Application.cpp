#include "Renderer/ShaderProgram.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"

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

	// GLEW initialisation
	if (glewInit() != GLEW_OK)
	{
		glfwDestroyWindow(window);
		glfwTerminate();
		return -1;
	}

	/// RECTANGLE RENDERING
	
	// Shaders
	ShaderProgram shaderProgram("Resources/Shaders/BasicVertex.shader", "Resources/Shaders/BasicFragment.shader");

	// Verticies
	GLfloat rectanglePositions[8] = {
		-0.4f, -0.4f,
		 0.4f, -0.4f,
		 0.4f,  0.4f,
		-0.4f,  0.4f
	};

	// Indicies
	GLuint indicies[6] = { 0, 1, 2, 3, 0, 2 };

	// Vertex array
	GLuint vertexArray;
	glCreateVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	// Vertex buffer
	VertexBuffer vertexBuffer(rectanglePositions, 8 * sizeof(GLfloat));
	vertexBuffer.Bind();

	// Vertex buffer layout
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), nullptr);
	glEnableVertexAttribArray(0);

	// Index buffer
	IndexBuffer indexBuffer(indicies, 6);
	indexBuffer.Bind();

	shaderProgram.Unuse();
	glBindVertexArray(0);
	vertexBuffer.Unbind();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		// Set a background color
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.5f, 0.2f, 0.2f, 1.f);

		shaderProgram.Use();
		glBindVertexArray(vertexArray);

		// Draw call
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		glfwSwapBuffers(window);	// Swap between front and back buffers

		glfwPollEvents();	// Manage window events (like closing, resizing...)
	}

	glDeleteVertexArrays(1, &vertexArray);

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}