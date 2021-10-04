#include "ApplicationUtils.h"

#include "Renderer/Renderer2D.h"
#include "Renderer/GraphicRectangle.h"

#include "Game/Pipes.h"
#include "Game/Flappy.h"

#include <vector>
#include <stdlib.h>
#include <time.h>


#include <GLM/gtc/matrix_transform.hpp>

static const Vector2D<float> WINDOW_SIZE(414.f, 736.f);

/**
 * .Change the height of the given pair of pipes randomly and place them out of the screen on the right side.
 * 
 * \param pipes the pair of pipes
 */
static void regeneratePipes(const Pipes& pipes)
{
	pipes.setBottomPipeHeight((float)(rand() % 150 + (int)(WINDOW_SIZE.y - 400)));
	pipes.setPositionX(WINDOW_SIZE.x * 2);
}

/**
 * .Manage pipes collision, movements and regeneration.
 * 
 * \param pipesVector the pipes
 * \param flappy the flappy instance that may collide with the pipes
 */
static void managePipes(const std::vector<Pipes*>& pipesVector, Flappy& flappy)
{
	for (const Pipes* pipes : pipesVector)
	{
		if (pipes->isColliding(flappy))
		{
			Color red(0.75f, 0.25f, 0.25f, 1.f);
			flappy.setColor(red);
		}

		if (pipes->reachedWindowEnd())
			regeneratePipes(*pipes);

		pipes->moveToLeft(); // Pipes constantly move to the left of the screen
	}
}

/**
 * .Manage the given flappy jump.
 * 
 * \param flappy The flappy instance
 * \param isJumping Used to determine when flappy has reached his maximum jump height
 */
static void manageFlappyJump(Flappy& flappy, bool& isJumping)
{
	if (flappy.firstJumpDone())
	{
		if (!flappy.isJumping())
		{
			flappy.applyGravity(isJumping);
			isJumping = false;
		}
		else
		{
			flappy.jump();
			isJumping = true;
		}
	}
}

/**
 * .Update and draw the given graphic shapes.
 * 
 * \param graphicRepresentations The graphic shapes to update and draw.
 * \param renderer The renderer used to draw the graphic shapes.
 */
static void updateGraphics(const std::vector<GraphicRectangle*>& graphicShapes, const Renderer2D& renderer)
{
	for (GraphicRectangle* graphicShape : graphicShapes)
	{
		graphicShape->checkUpdate();
		renderer.draw(*graphicShape);
	}
}

int main()
{
	// Window & OpenGL context creation using GLFW
	GLFWwindow* window = ApplicationUtils::createWindow((int)WINDOW_SIZE.x, (int)WINDOW_SIZE.y, "OpenFlappy", 4, 5);

	// GLEW initialisation
	if (!ApplicationUtils::glewInitialisation(true))
	{
		glfwDestroyWindow(window);
		glfwTerminate();
		return -1;
	}


	/// GAME SETUP
	srand((unsigned int)time(nullptr)); // Set the seed to randomize

	// Setup game graphics
	Renderer2D renderer(WINDOW_SIZE);
	std::vector<GraphicRectangle*> graphicRepresentations; // Gather all the graphic representations that will be drawn by the renderer (except the background)


	/// Background
	Texture backgroundTexture("Resources/Textures/background.png");
	const Rectangle background(0.0f, 0.0f, WINDOW_SIZE.x, WINDOW_SIZE.y, backgroundTexture);
	GraphicRectangle graphicBackground(background);


	/// Pipes initialisation
	Texture entryTexture("Resources/Textures/pipeEntry.png");
	Texture tubeTexture("Resources/Textures/pipeTube.png", 0, false);

	std::vector<Pipes*> allPipes; // Gather all the pipes of the game
	// We only need 3 pair of pipes that we are going to reposition every time (no need to constantly delete and create new ones)
	allPipes.push_back(new Pipes(300.f, WINDOW_SIZE.x + 750.f, WINDOW_SIZE.y, entryTexture, tubeTexture));
	allPipes.push_back(new Pipes(100.f, WINDOW_SIZE.x + 750.f + (WINDOW_SIZE.x - WINDOW_SIZE.x / 3), WINDOW_SIZE.y, entryTexture, tubeTexture));
	allPipes.push_back(new Pipes(500.f, WINDOW_SIZE.x + 750.f + (WINDOW_SIZE.x + WINDOW_SIZE.x / 3), WINDOW_SIZE.y, entryTexture, tubeTexture));
	
	// We add the graphic representations of the pipes
	/*for (const Pipes* pipes : allPipes)
	{
		graphicRepresentations.push_back(new GraphicRectangle(*pipes->getBottomPipe()->getPipeEntry()));
		graphicRepresentations.push_back(new GraphicRectangle(*pipes->getBottomPipe()->getPipeTube()));
		graphicRepresentations.push_back(new GraphicRectangle(*pipes->getTopPipe()->getPipeEntry()));
		graphicRepresentations.push_back(new GraphicRectangle(*pipes->getTopPipe()->getPipeTube()));
	}*/


	/// Flappy bird
	Texture flappyTexture("Resources/Textures/flappyBird.png");
	Vector2D<float> flappyStartPosition(100.f, WINDOW_SIZE.y / 2);
	Vector2D<float> flappySize(50.f, 50.f);
	Flappy flappy(flappyStartPosition, flappySize, flappyTexture, window);
	graphicRepresentations.push_back(new GraphicRectangle(flappy));
	bool isJumping = false;	// Used to determine when flappy has reached his maximum jump height


	flappy.setRotation(180.f);

	// MAIN LOOP
	while (!glfwWindowShouldClose(window))
	{
		renderer.clear();

		renderer.draw(graphicBackground); // Draw backgound first, and the other elements above
		//managePipes(allPipes, flappy);
		//manageFlappyJump(flappy, isJumping);
		updateGraphics(graphicRepresentations, renderer);

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