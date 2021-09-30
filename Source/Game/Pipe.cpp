#include "Pipe.h"

Pipe::Pipe(const float x, const float y, const float height, Texture& entryTexture, Texture& tubeTexture,
	const bool entryTop /*= true*/, const float width /*= 40.f*/, const float speed /*= 2.5f*/) : m_entryTop(entryTop), m_speed(speed)
{
	float yPipeEntry = height - PIPE_ENTRY_HEIGHT;
	float yPipeTube = y;
	if (!m_entryTop)
	{
		yPipeEntry = y;
		yPipeTube = y + PIPE_ENTRY_HEIGHT;
	}

	m_pipeEntry = new Rectangle(x, yPipeEntry, width, PIPE_ENTRY_HEIGHT, entryTexture);
	m_pipeTube = new Rectangle(x, yPipeTube, width, height - PIPE_ENTRY_HEIGHT, tubeTexture);
}

void Pipe::setPositionX(const float x) const
{
	m_pipeEntry->setPosition(x, m_pipeEntry->getPosition().y);
	m_pipeTube->setPosition(x, m_pipeTube->getPosition().y);

}

void Pipe::moveToLeft() const
{
	m_pipeEntry->setPosition(m_pipeEntry->getPosition().x - m_speed, m_pipeEntry->getPosition().y);
	m_pipeTube->setPosition(m_pipeTube->getPosition().x - m_speed, m_pipeTube->getPosition().y);
}

bool Pipe::reachedWindowEnd() const
{
	return (m_pipeEntry->getPosition().x + m_pipeEntry->getSize().x) < 0;
}

bool Pipe::isColliding(const Rectangle& rectangle) const
{
	return m_pipeEntry->isColliding(rectangle) || m_pipeTube->isColliding(rectangle);
}



void Pipe::setPositionY(const float y) const
{
	m_pipeEntry->setPosition(m_pipeEntry->getPosition().x, y);
	m_pipeTube->setPosition(m_pipeTube->getPosition().x, y + PIPE_ENTRY_HEIGHT);
}

void Pipe::setHeight(const float height) const
{
	m_pipeTube->setSize(m_pipeTube->getSize().x, height - PIPE_ENTRY_HEIGHT);

	if (m_entryTop)
		m_pipeEntry->setPosition(m_pipeTube->getPosition().x, m_pipeTube->getPosition().y + m_pipeTube->getSize().y);
	else
		m_pipeEntry->setPosition(m_pipeTube->getPosition().x, m_pipeTube->getPosition().y - PIPE_ENTRY_HEIGHT);
}

float Pipe::getHeight() const
{
	return m_pipeTube->getSize().y + m_pipeEntry->getSize().y;
}



Rectangle* Pipe::getPipeTube() const
{
	return m_pipeTube;
}

Rectangle* Pipe::getPipeEntry() const
{
	return m_pipeEntry;
}



Pipe::~Pipe()
{
	delete m_pipeEntry;
	delete m_pipeTube;
}