#pragma once

#include "Vector2D.h"
#include "../Renderer/Color.h"
#include "../Renderer/ShaderProgram.h"
#include "../Renderer/VertexArray.h"
#include "../Renderer/VertexBuffer.h"
#include "../Renderer/VertexBufferLayout.h"
#include "../Renderer/IndexBuffer.h"
#include "../Renderer/Texture.h"

class Rectangle
{
public:
	// Constructors using Vector2D<float>
	Rectangle(const Vector2D<float>& position, const Vector2D<float>& size);
	Rectangle(const Vector2D<float>& position, const Vector2D<float>& size, const Color& color);
	Rectangle(const Vector2D<float>& position, const Vector2D<float>& size, const Texture& texture);
	Rectangle(const Vector2D<float>& position, const Vector2D<float>& size, const Color& color, const Texture& texture);
	~Rectangle();

	// Setters
	void setPosition(const Vector2D<float>& position);
	void setSize(const Vector2D<float>& size);
	void setColor(const Color& color);
	void setTexture(const Texture& texture);

	// Getters
	Vector2D<float> getPosition() const;
	Vector2D<float> getSize() const;
	Color* getColor() const;

	ShaderProgram* getShaderProgram() const;
	VertexArray* getVertexArray() const;

private:
	// Specific to the shape
	Vector2D<float> m_position;
	Vector2D<float> m_size;

	Color* m_color;
	Texture* m_texture;

	// For OpenGL
	ShaderProgram* m_shaderProgram;
	VertexArray* m_vertexArray;
	VertexBuffer* m_vertexBuffer;
	VertexBufferLayout* m_vertexBufferLayout;
	IndexBuffer* m_indexBuffer;
	
	// To construct the object
	void build();
	void buildShaderProgram();
	void buildVertexBuffer();
};