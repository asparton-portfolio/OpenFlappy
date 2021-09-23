#pragma once

#include "../Renderer/ShaderProgram.h"
#include "../Renderer/VertexArray.h"
#include "../Renderer/IndexBuffer.h"
#include "../Renderer/Texture.h"

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

#include "Vector2D.h"
#include "../Renderer/Color.h"

#include <iostream>

/**
 * .Base class for any shape (rectangle, triangle, circle...) that will be draw using the renderer.
 */
class Shape
{
	/// <summary>
	/// TO BUILD THE GRAPHIC REPRESENTATION
	/// </summary>
public:
	virtual void buildGraphicRepresentation(const glm::mat4& projectionMatrix) = 0;
	void updateShaders(const glm::mat4& projectionMatrix)
	{ 
		m_shaderProgram->use();

		if (m_colorChanged)
		{
			m_shaderProgram->SetUniformColor("u_Color", m_color);
			m_colorChanged = false;
		}
			
		if (m_positionChanged)
		{
			m_shaderProgram->setUniformMat4("u_MVP", projectionMatrix * m_modelMatrix);
			m_positionChanged = false;
		}
			
		if (m_textureChanged)
		{
			m_texture->bind();
			m_shaderProgram->SetUniform1i("u_Texture", m_texture->getSamplerSlot());
			m_verticiesChanged = false;
		}
		
		m_shaderProgram->unuse();
	}

	// Needed by the renderer
	inline bool verticiesChanged() const { return m_verticiesChanged; }
	inline virtual bool uniformChanged() const { return m_colorChanged || m_positionChanged; }

	inline ShaderProgram* getShaderProgram() const { return m_shaderProgram; }
	inline VertexArray* getVertexArray() const { return m_vertexArray; }
	inline unsigned int getIndexBufferCount() const { return m_indexBuffer->getCount(); }

protected:

	// To build the graphic representation of the shape
	ShaderProgram* m_shaderProgram;
	VertexArray* m_vertexArray;
	VertexBuffer* m_vertexBuffer;
	VertexBufferLayout* m_vertexBufferLayout;
	IndexBuffer* m_indexBuffer;
	Texture* m_texture;

	// To know if we have to change something in the graphics pipeline before the draw call
	bool m_verticiesChanged;
	bool m_colorChanged;
	bool m_positionChanged;
	bool m_textureChanged;

	glm::mat4 m_modelMatrix;	// To position and scale up the shape on the view



	/// <summary>
	/// TO REPRESENT THE SHAPE
	/// </summary>
public:
	// Constructors
	inline Shape() = default;

	explicit Shape(const Vector2D<float>& position) :
		m_shaderProgram(nullptr), m_vertexArray(nullptr), m_vertexBuffer(nullptr), m_vertexBufferLayout(nullptr), m_indexBuffer(nullptr),
		m_texture(nullptr), m_verticiesChanged(true), m_colorChanged(true), m_positionChanged(true), m_textureChanged(false),
		m_modelMatrix(glm::translate(glm::mat4(1.f), glm::vec3(position.x, position.y, 0.f))), m_position(position), m_color() {}

	Shape(const Vector2D<float>& position, const Color& color) :
		m_shaderProgram(nullptr), m_vertexArray(nullptr), m_vertexBuffer(nullptr), m_vertexBufferLayout(nullptr), m_indexBuffer(nullptr), 
		m_texture(nullptr), m_verticiesChanged(true), m_colorChanged(true), m_positionChanged(true), m_textureChanged(false),
		m_modelMatrix(glm::translate(glm::mat4(1.f), glm::vec3(position.x, position.y, 0.f))), m_position(position), m_color(color) {}

	Shape(const Vector2D<float>& position, const Texture& texture) :
		m_shaderProgram(nullptr), m_vertexArray(nullptr), m_vertexBuffer(nullptr), m_vertexBufferLayout(nullptr), m_indexBuffer(nullptr),
		m_texture(new Texture(texture.getPath())), m_verticiesChanged(true), m_colorChanged(true), m_positionChanged(true), m_textureChanged(true),
		m_modelMatrix(glm::translate(glm::mat4(1.f), glm::vec3(position.x, position.y, 0.f))), m_position(position), m_color() {}

	Shape(const Vector2D<float>& position, const Color& color, const Texture& texture) :
		m_shaderProgram(nullptr), m_vertexArray(nullptr), m_vertexBuffer(nullptr), m_vertexBufferLayout(nullptr), m_indexBuffer(nullptr),
		m_texture(new Texture(texture.getPath())), m_verticiesChanged(true), m_colorChanged(true), m_positionChanged(true), m_textureChanged(true),
		m_modelMatrix(glm::translate(glm::mat4(1.f), glm::vec3(position.x, position.y, 0.f))), m_position(position), m_color(color) {}

	// Setters
	void setPosition(const Vector2D<float> position) 
	{
		m_position = position; 
		m_modelMatrix = glm::translate(glm::mat4(1.f), glm::vec3(position.x, position.y, 0.f));
		m_positionChanged = true;
	}

	void setColor(const Color& color) 
	{ 
		m_color = color; 
		m_colorChanged = true;
	}

	void setTexture(Texture* texture) 
	{ 
		if (texture && texture != m_texture)
		{
			m_textureChanged = true;
			if (!m_texture)
				m_verticiesChanged = true;
		}
		else if (!texture && m_texture)
			m_verticiesChanged = true;

		delete m_texture;
		m_texture = texture;
	}

	// Getters
	inline Vector2D<float> getPosition() const { return m_position; }
	inline Color getColor() const { return m_color; }

protected:
	Vector2D<float> m_position;
	Color m_color;
};