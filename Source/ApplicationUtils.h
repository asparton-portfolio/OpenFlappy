#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>

/**
 * .Usefull functions used to create the heart of the application (window & opengl intialisation...)
 */
class ApplicationUtils
{
public:

	/**
	 * .Create a GLFW window.
	 * 
	 * \param width The window's width
	 * \param height The window's height
	 * \param title The window's title/description
	 * \param openglMajorVersion The major version of opengl to use
	 * \param openglMinorVersion The minor version of opengl to use
	 * \param makeContextCurrent Make the created window the current context or not (true by default)
	 * \param swapInterval The minimum number of screen updates to wait for until the buffers are swapped by "glfwSwapBuffers"
	 * 
	 * \return A pointer to the created window or nullptr if an error occured.
	 */
	static GLFWwindow* createWindow(const int width, const int height, const char* title, const int openglMajorVersion, const int openglMinorVersion, 
		const bool makeContextCurrent = true, const int swapInterval = 1)
	{
		// GLFW initialisation
		if (glfwInit() != GLFW_TRUE)
			return nullptr;

		// OpenGL version
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, openglMajorVersion);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, openglMinorVersion);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		// Window creation
		GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr);
		if (!window)
		{
			glfwTerminate();
			return nullptr;
		}

		// Make context current if wanted
		if (makeContextCurrent)
			glfwMakeContextCurrent(window);

		glfwSwapInterval(swapInterval);

		return window;
	}

	/**
	 * .Initialse glew and possibly enable blending.
	 * 
	 * \param enableBlending Enable blending or not
	 * 
	 * \return true if glew has been sucessfully initialised, false otherwise.
	 */
	static bool glewInitialisation(const bool enableBlending)
	{
		if (glewInit() != GLEW_OK)
			return false;

		// Blending initialisation
		if (enableBlending)
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}

		return true;
	}

	/**
	 * .Free the memory for each pointer in the given vector.
	 * 
	 * \param vector The vector of pointers.
	 */
	template <typename T>
	static void freeVectorMemory(const std::vector<T*>& vector)
	{
		for (T* element : vector)
			delete element;
	}
};
