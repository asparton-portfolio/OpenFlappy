#include "Pipes.h"

Pipes::Pipes(const float bottomPipeHeight, const float startPositionX, const float windowSizeY, Texture& textureBottom, Texture& textureTop,
const float pipeWidth /*= 30.f*/, const float pipeGap /*= 100.f*/, const float speed /*= 2.f*/) :
	m_bottomPipe(), m_topPipe(), m_pipeGap(pipeGap), m_pipeWidth(pipeWidth), m_speed(speed), m_windowSizeY(windowSizeY)
{
	m_bottomPipe = new Rectangle(startPositionX, 0.f, m_pipeWidth, bottomPipeHeight, textureBottom);
	m_topPipe = new Rectangle(startPositionX, bottomPipeHeight + m_pipeGap, m_pipeWidth, m_windowSizeY - bottomPipeHeight - m_pipeGap, textureTop);
}

void Pipes::setPositionX(const float x) const
{
	m_bottomPipe->setPosition(x, m_bottomPipe->getPosition().y);
	m_topPipe->setPosition(x, m_topPipe->getPosition().y);
}

void Pipes::setBottomPipeHeight(const float height) const
{
	if (m_bottomPipe->getSize().y != height)
	{
		m_bottomPipe->setSize(m_pipeWidth, height);

		m_topPipe->setSize(m_pipeWidth, m_windowSizeY - height - m_pipeGap);
		m_topPipe->setPosition(m_bottomPipe->getPosition().x, height + m_pipeGap); // Have to reposition the top pipe after resizing it
	}
}

void Pipes::moveToLeft() const
{
	Vector2D<float> nextPosition = m_bottomPipe->getPosition();
	nextPosition.x -= m_speed;
	m_bottomPipe->setPosition(nextPosition);

	nextPosition.y = m_topPipe->getPosition().y;
	m_topPipe->setPosition(nextPosition);
}

bool Pipes::reachedWindowEnd() const
{
	return (m_bottomPipe->getPosition().x + m_bottomPipe->getSize().x) < 0;
}



Rectangle* Pipes::getBottomPipe() const
{
	return m_bottomPipe;
}

Rectangle* Pipes::getTopPipe() const
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