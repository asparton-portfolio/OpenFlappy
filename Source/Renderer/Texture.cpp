#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <STB/stb_image.h>

#include <iostream>

Texture::Texture(const char* texturePath, const GLint samplerSlot /*= 0*/, const bool flipVertically /*= true*/) :
	m_ID(0), m_samplerSlot(samplerSlot), m_isFlipped(flipVertically), m_path(texturePath)
{
	// Get texture data
	int width, height, bytesPerPixel;

	stbi_set_flip_vertically_on_load(0);
	if (m_isFlipped)
		stbi_set_flip_vertically_on_load(1);	// because the starting point of texture coordinates in opengl is the opposite considering the y axis

	unsigned char* textureData = stbi_load(texturePath, &width, &height, &bytesPerPixel, STBI_rgb_alpha);
	if (textureData)
	{
		// Create OpenGL texture
		glCreateTextures(GL_TEXTURE_2D, 1, &m_ID);
		bind();

		// Define texture parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		// Set texture datas
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
		unbind();
	}
	else
	{
		std::cout << "ERROR: Texture can't be loaded." << std::endl;
		m_path = nullptr;
	}
	stbi_image_free(textureData);
}

void Texture::bind() const
{
	glActiveTexture(GL_TEXTURE0 + m_samplerSlot);
	glBindTexture(GL_TEXTURE_2D, m_ID);
}

void Texture::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint Texture::getSamplerSlot() const
{
	return m_samplerSlot;
}

const char* Texture::getPath() const
{
	return m_path;
}

bool Texture::isFlipped() const
{
	return m_isFlipped;
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_ID);
}