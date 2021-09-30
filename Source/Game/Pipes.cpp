#include "Pipes.h"

Pipes::Pipes(const float bottomPipeHeight, const float startPositionX, const float windowSizeY, Texture& entryTexture, Texture& tubeTexture,
const float pipeWidth /*= 30.f*/, const float pipeGap /*= 100.f*/) :
	m_bottomPipe(), m_topPipe(), m_pipeGap(pipeGap), m_pipeWidth(pipeWidth), m_windowSizeY(windowSizeY)
{
	m_bottomPipe = new Pipe(startPositionX, 0.f, bottomPipeHeight, entryTexture, tubeTexture);
	m_topPipe = new Pipe(startPositionX, bottomPipeHeight + m_pipeGap, m_windowSizeY - bottomPipeHeight - m_pipeGap, entryTexture, tubeTexture, false);
}

void Pipes::setPositionX(const float x) const
{
	m_bottomPipe->setPositionX(x);
	m_topPipe->setPositionX(x);
}

void Pipes::setBottomPipeHeight(const float height) const
{
	if (m_bottomPipe->getHeight() != height)
	{
		m_bottomPipe->setHeight(height);

		m_topPipe->setHeight(m_windowSizeY - height - m_pipeGap);
		m_topPipe->setPositionY(height + m_pipeGap); // Have to reposition the top pipe after resizing it
	}
}

void Pipes::moveToLeft() const
{
	m_bottomPipe->moveToLeft();
	m_topPipe->moveToLeft();
}

bool Pipes::reachedWindowEnd() const
{
	return m_bottomPipe->reachedWindowEnd();
}



bool Pipes::isColliding(const Rectangle& rectangle) const
{
	return m_bottomPipe->isColliding(rectangle) || m_topPipe->isColliding(rectangle);
}

Pipe* Pipes::getBottomPipe() const
{
	return m_bottomPipe;
}

Pipe* Pipes::getTopPipe() const
{
	return m_topPipe;
}

float Pipes::getPipeWidth() const
{
	return m_pipeWidth;
}



Pipes::~Pipes()
{
	delete m_bottomPipe;
	delete m_topPipe;
}