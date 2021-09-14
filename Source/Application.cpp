#include "Renderer/ShaderProgram.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Texture.h"

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

	// Verticies
	GLfloat rectangleVerticies[16] = {
		-0.4f, -0.4f, 0.0f, 0.0f,
		 0.4f, -0.4f, 1.0f, 0.0f,
		 0.4f,  0.4f, 1.0f, 1.0f,
		-0.4f,  0.4f, 0.0f, 1.0f
	};

	// Indicies
	GLuint indicies[6] = { 0, 1, 2, 3, 0, 2 };

	// Shaders
	ShaderProgram shaderProgram("Resources/Shaders/BasicVertex.shader", "Resources/Shaders/BasicFragment.shader");

	// Texture
	Texture texture("Resources/Textures/flappyBird.png");
	texture.bind();
	shaderProgram.SetUniform1i("u_Texture", 0);
	shaderProgram.SetUniform4f("u_Color", 0.2f, 0.5f, 0.8f, 1.f);

	// Vertex array
	VertexArray vertexArray;
	vertexArray.bind();

	// Vertex buffer
	VertexBuffer vertexBuffer(rectangleVerticies, 16 * sizeof(GLfloat));
	vertexBuffer.bind();

	// Vertex buffer layout
	VertexBufferLayout vbLayout;
	vbLayout.Add<GLfloat>(2);
	vbLayout.Add<GLfloat>(2);
	vertexArray.setVertexBufferLayout(vbLayout);

	// Index buffer
	IndexBuffer indexBuffer(indicies, 6);
	indexBuffer.bind();

	shaderProgram.unuse();
	vertexArray.unbind();
	vertexBuffer.unbind();
	indexBuffer.unbind();

	GLfloat green = 0.0f;
	float variation = 0.05f;

	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		// Set a background color
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.5f, 0.2f, 0.2f, 1.f);

		if (green > 1.0f || green < 0.0f)
			variation = -variation;
		green += variation;

		shaderProgram.use();
		vertexArray.bind();

		// Draw call
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		glfwSwapBuffers(window);	// Swap between front and back buffers

		glfwPollEvents();	// Manage window events (like closing, resizing...)
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}