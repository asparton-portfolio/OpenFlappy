#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <STB/stb_image.h>

#include <iostream>

Texture::Texture(const char* texturePath) : m_ID(0), m_samplerSlot(0)
{
	// Get texture data
	int width, height, bytesPerPixel;
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
	}
	stbi_image_free(textureData);
}

void Texture::bind(const int samplerSlot /* = 0*/)
{
	if (m_samplerSlot != samplerSlot)
		m_samplerSlot = samplerSlot;

	glBindTexture(GL_TEXTURE_2D, m_ID + m_samplerSlot);
}

void Texture::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

GLint Texture::getSamplerSlot() const
{
	return m_samplerSlot;
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_ID);
}