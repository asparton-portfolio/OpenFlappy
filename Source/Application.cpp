#include "ApplicationUtils.h"

#include "Renderer/Renderer2D.h"
#include "Renderer/GraphicRectangle.h"

#include "Game/PairOfPipes.h"
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
static void regeneratePipes(const PairOfPipes& pair)
{
	pair.setBottomPipeHeight((float)(rand() % 150 + (int)(WINDOW_SIZE.y - 400)));
	pair.setPositionX(WINDOW_SIZE.x * 2);
}

/**
 * .Manage pipes movements and regeneration.
 * 
 * \param pipesVector the pipes
 */
static void managePipes(const std::vector<PairOfPipes*>& allPairOfPipes)
{
	for (const PairOfPipes* pair : allPairOfPipes)
	{
		if (pair->reachedWindowEnd())
			regeneratePipes(*pair);

		pair->moveToLeft(); // Pipes constantly move to the left of the screen
	}
}

/**
 * .Manage the given flappy jump.
 * 
 * \param flappy The flappy instance
 * \param isJumping Used to determine when flappy has reached his maximum jump height
 * \return true if flappy collided with a pipe or the ground, false otherwise.
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
			if (flappy.getRotation() != -25.f)
				flappy.setRotation(25.f);
		}
	}
}

/**
 * .Determine wether the given flappy is colliding with one of the pipe or with the ground or nothing.
 * 
 * \param allPairOfPipes all the pair of pipes of the game.
 * \param ground the rectangle representing the ground collision box.
 * \param flappy the flappy instance.
 * \return true if flappy is colliding with one of the pipe or with the ground, false otherwise.
 */
static bool isFlappyColliding(const std::vector<PairOfPipes*>& allPairOfPipes, const Rectangle& ground, const Flappy& flappy)
{
	if (flappy.isColliding(ground))
		return true;

	for (const PairOfPipes* pair : allPairOfPipes)
	{
		if (pair->isColliding(flappy))
			return true;
	}

	return false;
}

/**
 * .Called when clicked on restart button, reset all the pipes position and height.
 * 
 * \param allPairOfPipes all the pair of pipes of the game.
 */
static void resetAllPairOfPipes(std::vector<PairOfPipes*>& allPairOfPipes)
{
	for (const PairOfPipes* pair : allPairOfPipes)
		pair->setBottomPipeHeight((float)(rand() % 150 + (int)(WINDOW_SIZE.y - 400)));

	allPairOfPipes[0]->setPositionX(WINDOW_SIZE.x + 250.f);
	allPairOfPipes[1]->setPositionX(WINDOW_SIZE.x + 250.f + (WINDOW_SIZE.x - WINDOW_SIZE.x / 3));
	allPairOfPipes[2]->setPositionX(WINDOW_SIZE.x + 250.f + (WINDOW_SIZE.x + WINDOW_SIZE.x / 3));
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
	const Rectangle background(0.f, 0.f, WINDOW_SIZE.x, WINDOW_SIZE.y, backgroundTexture);
	GraphicRectangle graphicBackground(background);


	/// Ground
	const Rectangle groundCollisionBox(0.f, 90.f, WINDOW_SIZE.x, 1.f);

	/// Pipes initialisation
	Texture entryTexture("Resources/Textures/pipeEntry.png");
	Texture tubeTexture("Resources/Textures/pipeTube.png", 0, false);

	std::vector<PairOfPipes*> allPairOfPipes; // Gather all the pipes of the game

	// We only need 3 pair of pipes that we are going to reposition every time (no need to constantly delete and create new ones)
	allPairOfPipes.push_back(new PairOfPipes((float)(rand() % 150 + (int)(WINDOW_SIZE.y - 400)), 
		WINDOW_SIZE.x + 250.f, WINDOW_SIZE.y, entryTexture, tubeTexture));

	allPairOfPipes.push_back(new PairOfPipes((float)(rand() % 150 + (int)(WINDOW_SIZE.y - 400)),
		WINDOW_SIZE.x + 250.f + (WINDOW_SIZE.x - WINDOW_SIZE.x / 3), WINDOW_SIZE.y, entryTexture, tubeTexture));

	allPairOfPipes.push_back(new PairOfPipes((float)(rand() % 150 + (int)(WINDOW_SIZE.y - 400)),
		WINDOW_SIZE.x + 250.f + (WINDOW_SIZE.x + WINDOW_SIZE.x / 3), WINDOW_SIZE.y, entryTexture, tubeTexture));
	
	// We add the graphic representations of the pipes
	for (const PairOfPipes* pipes : allPairOfPipes)
	{
		graphicRepresentations.push_back(new GraphicRectangle(*pipes->getBottomPipe()->getPipeEntry()));
		graphicRepresentations.push_back(new GraphicRectangle(*pipes->getBottomPipe()->getPipeTube()));
		graphicRepresentations.push_back(new GraphicRectangle(*pipes->getTopPipe()->getPipeEntry()));
		graphicRepresentations.push_back(new GraphicRectangle(*pipes->getTopPipe()->getPipeTube()));
	}


	/// Flappy bird
	Texture flappyTexture("Resources/Textures/flappyBird.png");
	const Vector2D<float> flappyStartPosition(WINDOW_SIZE.x / 4, WINDOW_SIZE.y / 2);
	const Vector2D<float> flappySize(50.f, 50.f);
	Flappy flappy(flappyStartPosition, flappySize, flappyTexture, window, AnchorPointLocation::CENTER);
	graphicRepresentations.push_back(new GraphicRectangle(flappy));
	bool isJumping = false;	// Used to determine when flappy has reached his maximum jump height


	/// Game over
	bool gameOver = false;
	const Color gameOverColor(0.2f, 0.2f, 0.2f, 0.6f);
	const Rectangle gameOverBackground(0.f, 0.f, WINDOW_SIZE.x, WINDOW_SIZE.y, gameOverColor);
	GraphicRectangle graphicGameOverBackground(gameOverBackground);

	Texture restartButtonTexture("Resources/Textures/restartButton.png");
	const Vector2D<float> buttonSize(136.f, 47.f);
	const Rectangle restartButton(WINDOW_SIZE.x / 2 - buttonSize.x / 2, WINDOW_SIZE.y / 2 - buttonSize.y / 2, 
								  buttonSize.x, buttonSize.y, restartButtonTexture);
	GraphicRectangle graphicRestartButton(restartButton);

	// MAIN LOOP
	while (!glfwWindowShouldClose(window))
	{
		renderer.clear();
		renderer.draw(graphicBackground); // Draw backgound first, and the other elements above

		if (!gameOver)
		{
			if (flappy.firstJumpDone())
				managePipes(allPairOfPipes);

			manageFlappyJump(flappy, isJumping);
			gameOver = isFlappyColliding(allPairOfPipes, groundCollisionBox, flappy);
		}

		updateGraphics(graphicRepresentations, renderer);
		if (gameOver)
		{
			renderer.draw(graphicGameOverBackground);
			renderer.draw(graphicRestartButton);

			Vector2D<double> currentMousePosition;
			glfwGetCursorPos(window, &currentMousePosition.x, &currentMousePosition.y);
			int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);

			if (state == GLFW_RELEASE &&
				currentMousePosition.x >= restartButton.getPosition().x &&
				currentMousePosition.x <= restartButton.getPosition().x + restartButton.getSize().x &&
				currentMousePosition.y >= restartButton.getPosition().y &&
				currentMousePosition.y <= restartButton.getPosition().y + restartButton.getSize().y)
			{
				gameOver = false;
				flappy.setPosition(flappyStartPosition);
				flappy.setRotation(0.f);
				flappy.resetFirstJumpDone();
				resetAllPairOfPipes(allPairOfPipes);
			}
		}

		glfwSwapBuffers(window); // Swap between front and back buffers
		glfwPollEvents(); // Manage window events (like closing, resizing...)
	}

	// Free the allocated memory
	ApplicationUtils::freeVectorMemory(allPairOfPipes);
	ApplicationUtils::freeVectorMemory(graphicRepresentations);

	// Terminate GLFW & the application
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}