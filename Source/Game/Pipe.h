#pragma once

#include "../Renderer/Shapes/Rectangle.h"

class Pipe
{
public:
	Pipe(const float x, const float y, const float height, Texture& entryTexture, Texture& tubeTexture, 
		const bool entryTop = true, const float width = 40.f, const float speed = 2.5f);
	~Pipe();

	/**
	 * .Set a new position for the x axis for the pipe.
	 *
	 * \param x The new position of the pipe on the x axis.
	 */
	void setPositionX(const float x) const;

	/**
	 * .Decrease the position of the pipe on the x axis by the speed.
	 */
	void moveToLeft() const;

	/**
	 * \return true if the left side of the pipe has reached the end of the screen, false otherwise
	 */
	bool reachedWindowEnd() const;

	/**
	 * .Determine wether the given rectangle is colliding with the pipe.
	 *
	 * \param rectangle the rectangle
	 * \return true if the given rectangle is colliding with the pipe, false otherwise.
	 */
	bool isColliding(const Rectangle& rectangle) const;

	void setPositionY(const float y) const;
	void setHeight(const float height) const;
	float getHeight() const;

	Rectangle* getPipeTube() const;
	Rectangle* getPipeEntry() const;

private:
	Rectangle* m_pipeTube;
	Rectangle* m_pipeEntry;
	bool m_entryTop;

	float m_speed;

	static const int PIPE_ENTRY_HEIGHT = 25;
};
