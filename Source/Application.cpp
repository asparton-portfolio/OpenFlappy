#include "ApplicationUtils.h"

#include "Renderer/Renderer2D.h"
#include "Renderer/GraphicRectangle.h"

#include "Game/Pipes.h"

#include <vector>
#include <stdlib.h>
#include <time.h>
#include <iostream>

int main()
{
	// Window & OpenGL context creation using GLFW
	const Vector2D<float> WINDOW_SIZE(414.f, 736.f);
	GLFWwindow* window = ApplicationUtils::createWindow((int)WINDOW_SIZE.x, (int)WINDOW_SIZE.y, "OpenFlappy", 4, 5);

	// GLEW initialisation
	if (!ApplicationUtils::glewInitialisation(true))
	{
		glfwDestroyWindow(window);
		glfwTerminate();
		return -1;
	}



	// Set the seed to randomize
	srand((unsigned int)time(nullptr));

	// Setup game graphics
	Renderer2D renderer(WINDOW_SIZE);
	std::vector<GraphicRectangle*> graphicRepresentations; // Gather all the graphic representations that will be drawn by the renderer (except the background)



	/// Background
	Texture backgroundTexture("Resources/Textures/background.png");
	const Rectangle background(0.0f, 0.0f, WINDOW_SIZE.x, WINDOW_SIZE.y, backgroundTexture);
	GraphicRectangle graphicBackground(background);



	/// Pipes initialisation
	const int BOTTOM_PIPE_HEIGHT_RANGE = 150 + (int)(WINDOW_SIZE.y - 200);
	Texture entryTexture("Resources/Textures/pipeEntry.png");
	Texture tubeTexture("Resources/Textures/pipeTube.png", 0, false);

	std::vector<Pipes*> allPipes; // Gather all the pipes of the game
	// We only need 3 pair of pipes that we are going to reposition every time (no need to constantly delete and create new ones)
	allPipes.push_back(new Pipes(300.f, WINDOW_SIZE.x, WINDOW_SIZE.y, entryTexture, tubeTexture));
	allPipes.push_back(new Pipes(100.f, WINDOW_SIZE.x + (WINDOW_SIZE.x - WINDOW_SIZE.x / 3), WINDOW_SIZE.y, entryTexture, tubeTexture));
	allPipes.push_back(new Pipes(500.f, WINDOW_SIZE.x + (WINDOW_SIZE.x + WINDOW_SIZE.x / 3), WINDOW_SIZE.y, entryTexture, tubeTexture));
	
	// We add the graphic representations of the pipes
	for (const Pipes* pipes : allPipes)
	{
		graphicRepresentations.push_back(new GraphicRectangle(*pipes->getBottomPipe()->getPipeEntry()));
		graphicRepresentations.push_back(new GraphicRectangle(*pipes->getBottomPipe()->getPipeTube()));
		graphicRepresentations.push_back(new GraphicRectangle(*pipes->getTopPipe()->getPipeEntry()));
		graphicRepresentations.push_back(new GraphicRectangle(*pipes->getTopPipe()->getPipeTube()));
	}


	
	/// Flappy bird
	Texture flappyTexture("Resources/Textures/flappyBird.png");
	Rectangle flappy(50.f, 600.f, 50.f, 50.f, flappyTexture);
	graphicRepresentations.push_back(new GraphicRectangle(flappy));



	// MAIN LOOP
	while (!glfwWindowShouldClose(window))
	{
		renderer.clear();
		renderer.draw(graphicBackground); // Draw backgound first, and the other elements above

		// Pipes management
		for (const Pipes* pipes : allPipes)
		{
			if (pipes->isColliding(flappy))
			{
				Color red(0.75f, 0.25f, 0.25f, 1.f);
				flappy.setColor(red);
			}

			if (pipes->reachedWindowEnd())
			{
				pipes->setBottomPipeHeight((float)(rand() % BOTTOM_PIPE_HEIGHT_RANGE));
				pipes->setPositionX(WINDOW_SIZE.x * 2);
			}

			pipes->moveToLeft(); // Pipes constantly move to the left of the screen
		}

		// Update and draw all the graphic elements
		for (GraphicRectangle* graphicRepresentation : graphicRepresentations)
		{
			graphicRepresentation->checkUpdate();
			renderer.draw(*graphicRepresentation);
		}

		glfwSwapBuffers(window); // Swap between front and back buffers
		glfwPollEvents(); // Manage window events (like closing, resizing...)
	}


	// Free the allocated memory
	ApplicationUtils::freeVectorMemory(allPipes);
	ApplicationUtils::freeVectorMemory(graphicRepresentations);

	// Terminate GLFW & the application
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}