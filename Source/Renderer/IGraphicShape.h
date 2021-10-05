#pragma once

#include <GLM/glm.hpp>

class IShape;
class ShaderProgram;
class VertexArray;

/**
 * .Gather all the methods that a graphic representation of a shape has to have.
 */
class IGraphicShape
{
public:

	/**
	 * .Build all the graphic components needed to draw the shape associated.
	 * 
	 * \param projectionMatrix the projection matrix of the renderer
	 */
	virtual void buildGraphicRepresentation(const glm::mat4& projectionMatrix) = 0;

	/**
	 * .Update the shader program if an information need to be changed (position, color, texture...)
	 * 
	 * \param projectionMatrix the projection matrix of the renderer
	 */
	virtual void updateShaders(const glm::mat4& projectionMatrix) = 0;

	/**
	 * .Build the vertex buffer associated with the shape and bind it with the current vertex array.
	 */
	virtual void buildAndBindVertexBuffer() = 0;

	/**
	 * \return the shape associated with this graphic representation
	 */
	virtual IShape* getAssociatedShape() const = 0;

	/**
	 * \return the shader program associated with the shape
	 */
	virtual ShaderProgram* getShaderProgram() const = 0;

	/**
	 * \return the vertex array associated with the shape
	 */
	virtual VertexArray* getVertexArray() const = 0;

	/**
	 * \return the index buffer count associated with the shape (number of verticies to draw)
	 */
	virtual unsigned int getIndexBufferCount() const = 0;



	/**
	 * .Check if the associated shape changed (position, color, texture, size...) to prepare updating the graphic representation
	 */
	virtual void checkUpdate() = 0;

	/**
	 * \return true if an information need to be updated in the shader program, false othetwise
	 */
	virtual bool shaderInfoChanged() const = 0;

	/**
	 * \return true if an information need to be updated in the buffers (build necessary), false othetwise
	 */
	virtual bool bufferVerticiesChanged() const = 0;

protected:

	/**
	 * .Create the shader program associated with the shape
	 */
	virtual void buildShaderProgram() = 0;

	/**
	 * .Build the vertex buffer associated with the shape
	 */
	virtual void buildVertexBuffer() = 0;
};
