#pragma once

#include "../Shapes/Rectangle.h"

/**
 * .Represents a pair of Pipes composed by two rectangles.
 *  - Can change of size and postion.
 *  - Can collide with another rectangle (not implemented yet).
 */
class Pipes
{
public:
	Pipes(const float bottomPipeHeight, const float startPositionX, const float windowSizeY, Texture& textureBottom, Texture& textureTop,
		const float pipeWidth = 40.f, const float pipeGap = 150.f, const float speed = 1.5f);
	~Pipes();

	/**
	 * .Set a new position for the x axis for the two pipes.
	 * 
	 * \param x The new position of the pipes on the x axis.
	 */
	void setPositionX(const float x) const;

	/**
	 * .Set the height of the bottom pipe (and adjust the height of the top one).
	 * 
	 * \param height The new height of the bottom pipe.
	 */
	void setBottomPipeHeight(const float height) const;

	/**
	 * .Decrease the position of the two pipes on the x axis by the speed.
	 */
	void moveToLeft() const;

	bool reachedWindowEnd() const;

	Rectangle* getBottomPipe() const;
	Rectangle* getTopPipe() const;
	float getPipeWidth() const;

private:
	Rectangle* m_bottomPipe;
	Rectangle* m_topPipe;
	float m_pipeGap;
	float m_pipeWidth;
	float m_speed;

	const float m_windowSizeY;
};
