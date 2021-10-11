#include "ApplicationUtils.h"
#include "Game/GameLogic.h"

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

/**
 * .Display the score on the screen using ImGui.
 * 
 * \param score the current score.
 */
static void displayScore(const unsigned int score)
{
	ImGui_ImplGlfwGL3_NewFrame();

	ImGui::Begin("Score");
	ImGui::SetWindowPos(ImVec2(WINDOW_SIZE.x / 2 - ImGui::GetWindowSize().x / 2, 10));
	ImGui::Text("Score: %d", score);
	ImGui::End();

	ImGui::Render();
	ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
}

int main()
{
	// Window & OpenGL context creation using GLFW
	GLFWwindow* window = ApplicationUtils::createWindow((int)WINDOW_SIZE.x, (int)WINDOW_SIZE.y, "OpenFlappy", 4, 5);
	glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);

	// GLEW initialisation
	if (!ApplicationUtils::glewInitialisation(true))
	{
		glfwDestroyWindow(window);
		glfwTerminate();
		return -1;
	}

	// ImGui initialisation
	ApplicationUtils::ImGuiInitialisation(window, false);

	srand((unsigned int)time(nullptr)); // Set the seed to randomize

	#pragma region Game initialisation

	// Setup game graphics
	Renderer2D renderer(WINDOW_SIZE);
	std::vector<GraphicRectangle*> graphicRepresentations; // Gather all the graphic representations that will be drawn by the renderer (except the background)


	/// Background
	Texture backgroundTexture("Resources/Textures/background.png");
	const Rectangle background(0.f, 0.f, WINDOW_SIZE.x, WINDOW_SIZE.y, backgroundTexture);
	GraphicRectangle graphicBackground(background);


	/// Ground collision
	const Rectangle groundCollisionBox(0.f, 90.f, WINDOW_SIZE.x, 1.f);


	/// Pipes
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
	// Background
	bool gameOver = false;
	const Color gameOverColor(0.2f, 0.2f, 0.2f, 0.6f);
	const Rectangle gameOverBackground(0.f, 0.f, WINDOW_SIZE.x, WINDOW_SIZE.y, gameOverColor);
	GraphicRectangle graphicGameOverBackground(gameOverBackground);

	// Restart button
	Texture restartButtonTexture("Resources/Textures/restartButton.png");
	const Vector2D<float> buttonSize(136.f, 47.f);
	const Vector2D<float> buttonPosition(WINDOW_SIZE.x / 2 - buttonSize.x / 2, WINDOW_SIZE.y / 2 - buttonSize.y / 2);
	const Button restartButton(buttonPosition, buttonSize, restartButtonTexture, window);
	GraphicRectangle graphicRestartButton(restartButton);

	/// Score
	unsigned int score = 0;

	#pragma endregion

	// MAIN LOOP
	while (!glfwWindowShouldClose(window))
	{
		renderer.clear();
		renderer.draw(graphicBackground); // Draw backgound first, and the other elements above
		updateGraphics(graphicRepresentations, renderer);

		if (!gameOver)
		{
			if (flappy.firstJumpDone())
				GameLogic::managePipes(allPairOfPipes);

			GameLogic::manageFlappyJump(flappy, isJumping);
			gameOver = GameLogic::isFlappyColliding(allPairOfPipes, groundCollisionBox, flappy);

			if (!gameOver && GameLogic::isFlappyBetweenPipes(allPairOfPipes, flappy))
				score++;
		}
		else
		{
			renderer.draw(graphicGameOverBackground);
			renderer.draw(graphicRestartButton);

			if (restartButton.isPressed(GLFW_MOUSE_BUTTON_LEFT))
			{
				GameLogic::resetGame(flappy, flappyStartPosition, allPairOfPipes);
				score = 0;
				gameOver = false;
			}
		}
		displayScore(score);

		glfwSwapBuffers(window); // Swap between front and back buffers
		glfwPollEvents(); // Manage window events (like closing, resizing...)
	}

	// Free the allocated memory
	ApplicationUtils::freeVectorMemory(allPairOfPipes);
	ApplicationUtils::freeVectorMemory(graphicRepresentations);

	// Terminate GLFW & ImGui & the application
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}