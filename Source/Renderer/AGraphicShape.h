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

	glm::mat4 m_translationMatrix; // Used to position the shape on the screen
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
	void buildVertexBuffer() override = 0;
};
