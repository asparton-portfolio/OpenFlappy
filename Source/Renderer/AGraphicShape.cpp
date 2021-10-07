#include "AGraphicShape.h"

#include <GLM/gtc/matrix_transform.hpp>

AGraphicShape::AGraphicShape(IShape* shape) : m_shape(shape), m_rotation(), m_color(m_shape->getColor()), m_texture(m_shape->getTexture())
{
	m_translationMatrix = glm::translate(glm::mat4(1.f), glm::vec3(m_shape->getPosition().x, m_shape->getPosition().y, 0.f));

	// To correctly update the associated shaders
	m_bufferVerticiesChanged = true;
	m_colorChanged = true;
	m_positionChanged = true;
	m_textureChanged = false;
	if (m_texture)
		m_textureChanged = true;

	m_shaderProgram = nullptr;
	m_vertexArray = nullptr;
	m_vertexBuffer = nullptr;
	m_vertexBufferLayout = nullptr;
	m_indexBuffer = nullptr;	// NEED TO BE INITIALIZED IN THE EXTENSIONS OF THE CLASS
}

void AGraphicShape::buildShaderProgram()
{
	std::string shaderName = "Color";
	if (m_texture)
		shaderName = "Texture";

	m_shaderProgram = new ShaderProgram("Resources/Shaders/" + shaderName + "Vertex.shader", "Resources/Shaders/" + shaderName + "Fragment.shader");
}

void AGraphicShape::updateShaders(const glm::mat4& projectionMatrix)
{
	m_shaderProgram->use();

	if (m_colorChanged)
	{
		m_shaderProgram->SetUniformColor("u_Color", m_shape->getColor());
		m_colorChanged = false;
	}

	if (m_positionChanged)
	{
		m_shaderProgram->setUniformMat4("u_MVP", projectionMatrix * m_translationMatrix);
		m_positionChanged = false;
	}

	if (m_textureChanged)
	{
		m_texture->bind();
		m_shaderProgram->SetUniform1i("u_Texture", m_texture->getSamplerSlot());
		m_textureChanged = false;
	}

	m_shaderProgram->unuse();
}



void AGraphicShape::checkUpdate()
{
	glm::mat4 shapeTranslationMatrix = glm::translate(glm::mat4(1.f), glm::vec3(m_shape->getPosition().x, m_shape->getPosition().y, 0.f));
	if (shapeTranslationMatrix != m_translationMatrix)
	{
		m_positionChanged = true;
		m_translationMatrix = shapeTranslationMatrix;
	}

	if (m_shape->getRotation() != m_rotation)
	{
		m_bufferVerticiesChanged = true;
		m_rotation = m_shape->getRotation();
	}

	if (m_shape->getAnchorPoint() != m_anchorPoint)
	{
		m_anchorPoint = m_shape->getAnchorPoint();
		m_bufferVerticiesChanged = true;
	}

	if (m_shape->getColor().red != m_color.red ||
		m_shape->getColor().green != m_color.green ||
		m_shape->getColor().blue != m_color.blue ||
		m_shape->getColor().alpha != m_color.alpha)
		m_colorChanged = true;

	if (m_shape->getTexture() != m_texture)
	{
		m_textureChanged = true;
		if ((m_shape->getTexture() && !m_texture) || (!m_shape->getTexture() && m_texture))
			m_bufferVerticiesChanged = true;

		m_texture = m_shape->getTexture();
	}
}

bool AGraphicShape::shaderInfoChanged() const
{
	return m_colorChanged || m_positionChanged || m_textureChanged;
}

bool AGraphicShape::bufferVerticiesChanged() const
{
	return m_bufferVerticiesChanged;
}

Vector2D<float> AGraphicShape::getPositionByRotation(const float x, const float y, const float& rotation)
{
	return Vector2D<float>((x * glm::cos(glm::radians(rotation))) - (y * glm::sin(glm::radians(rotation))),
						   (x * glm::sin(glm::radians(rotation))) + (y * glm::cos(glm::radians(rotation))));
}



IShape* AGraphicShape::getAssociatedShape() const
{
	return m_shape;
}

ShaderProgram* AGraphicShape::getShaderProgram() const
{
    return m_shaderProgram;
}

VertexArray* AGraphicShape::getVertexArray() const
{
    return m_vertexArray;
}

unsigned int AGraphicShape::getIndexBufferCount() const
{
    return m_indexBuffer->getCount();
}