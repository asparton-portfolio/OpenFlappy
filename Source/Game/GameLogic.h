#pragma once

#include "../Renderer/Renderer2D.h"
#include "../Renderer/GraphicRectangle.h"

#include "PairOfPipes.h"
#include "Flappy.h"
#include "Button.h"

#include <vector>
#include <stdlib.h>
#include <time.h>

static const Vector2D<float> WINDOW_SIZE(414.f, 736.f);

/**
 * .Contains flappy bird game logic needed (static).
 */
class GameLogic
{
public:

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
			if (pair->isColliding(flappy.getCollisionBox()))
				return true;
		}

		return false;
	}

	/**
	 * .Determine whether the left side of flappy is equal to the right side of a pair of pipes or not.
	 * 
	 * \param allPairOfPipes all the pair of pipes of the game
	 * \param flappy the flappy instance
	 * \return true if the left side of flappy is equal to the right side of a pair of pipes, false otherwise.
	 */
	static bool isFlappyBetweenPipes(const std::vector<PairOfPipes*>& allPairOfPipes, const Flappy& flappy)
	{
		for (const PairOfPipes* pair : allPairOfPipes)
		{
			float pipesRightSide = pair->getBottomPipe()->getPipeEntry()->getPosition().x + pair->getBottomPipe()->getPipeEntry()->getSize().x;
			if (flappy.getPosition().x >= pipesRightSide - 1 && flappy.getPosition().x <= pipesRightSide + 1)
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

	static void resetGame(Flappy& flappy, const Vector2D<float> flappyStartPosition, std::vector<PairOfPipes*>& allPairOfPipes)
	{
		flappy.setPosition(flappyStartPosition);
		flappy.setRotation(0.f);
		flappy.resetFirstJumpDone();
		GameLogic::resetAllPairOfPipes(allPairOfPipes);
	}
};