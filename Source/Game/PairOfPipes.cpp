#include "PairOfPipes.h"

PairOfPipes::PairOfPipes(const float bottomPipeHeight, const float startPositionX, const float windowSizeY, Texture& entryTexture, Texture& tubeTexture,
const float pipeWidth /*= 30.f*/, const float pipeGap /*= 100.f*/) :
	m_bottomPipe(), m_topPipe(), m_pipeGap(pipeGap), m_pipeWidth(pipeWidth), m_windowSizeY(windowSizeY)
{
	m_bottomPipe = new Pipe(startPositionX, 0.f, bottomPipeHeight, entryTexture, tubeTexture);
	m_topPipe = new Pipe(startPositionX, bottomPipeHeight + m_pipeGap, m_windowSizeY - bottomPipeHeight - m_pipeGap, entryTexture, tubeTexture, false);
}

void PairOfPipes::setPositionX(const float x) const
{
	m_bottomPipe->setPositionX(x);
	m_topPipe->setPositionX(x);
}

void PairOfPipes::setBottomPipeHeight(const float height) const
{
	if (m_bottomPipe->getHeight() != height)
	{
		m_bottomPipe->setHeight(height);

		m_topPipe->setHeight(m_windowSizeY - height - m_pipeGap);
		m_topPipe->setPositionY(height + m_pipeGap); // Have to reposition the top pipe after resizing it
	}
}

void PairOfPipes::moveToLeft() const
{
	m_bottomPipe->moveToLeft();
	m_topPipe->moveToLeft();
}

bool PairOfPipes::reachedWindowEnd() const
{
	return m_bottomPipe->reachedWindowEnd();
}



bool PairOfPipes::isColliding(const Rectangle& rectangle) const
{
	return m_bottomPipe->isColliding(rectangle) || m_topPipe->isColliding(rectangle);
}

Pipe* PairOfPipes::getBottomPipe() const
{
	return m_bottomPipe;
}

Pipe* PairOfPipes::getTopPipe() const
{
	return m_topPipe;
}

float PairOfPipes::getPipeWidth() const
{
	return m_pipeWidth;
}



PairOfPipes::~PairOfPipes()
{
	delete m_bottomPipe;
	delete m_topPipe;
}