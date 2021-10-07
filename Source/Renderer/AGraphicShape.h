#pragma once

#include "IGraphicShape.h"

#include "../Shapes/IShape.h"
#include "../Renderer/VertexArray.h"
#include "../Renderer/ShaderProgram.h"
#include "../Renderer/IndexBuffer.h"

/**
 * .Graphic representation of any shape (abstract)
 */
class AGraphicShape : public IGraphicShape
{
public:
	explicit AGraphicShape(IShape* shape);

	void buildGraphicRepresentation(const glm::mat4& projectionMatrix) override = 0;
	void updateShaders(const glm::mat4& projectionMatrix) final;

	IShape* getAssociatedShape() const final;
	ShaderProgram* getShaderProgram() const final;
	VertexArray* getVertexArray() const final;
	unsigned int getIndexBufferCount() const final;

	void checkUpdate() override;
	bool shaderInfoChanged() const override;
	bool bufferVerticiesChanged() const override;

protected:
	IShape* m_shape; // A pointer to the associated shape

	AnchorPointLocation m_anchorPoint; // The (0;0) location of the shape
	glm::mat4 m_translationMatrix; // Used to position the shape on the screen
	float m_rotation;
	Color m_color;
	Texture* m_texture; // Not mandatory (can be nullptr)


	// All the opengl elements that we need to draw this representation on the screen
	ShaderProgram* m_shaderProgram;
	VertexArray* m_vertexArray;
	VertexBuffer* m_vertexBuffer;
	VertexBufferLayout* m_vertexBufferLayout;
	IndexBuffer* m_indexBuffer;

	bool m_colorChanged;
	bool m_positionChanged;
	bool m_textureChanged;
	bool m_bufferVerticiesChanged;

	void buildShaderProgram() final;

	/**
	 * .Determines the new position depending on the given rotation in angle.
	 *
	 * \param x the position on the x axis.
	 * \param y the position on the y axis.
	 * \param rotation the rotation to add in angle (negative = anticlockwise | positive = clockwise).
	 * \return the position plus the given rotation.
	 */
	static Vector2D<float> getPositionByRotation(const float x, const float y, const float& rotation);
};