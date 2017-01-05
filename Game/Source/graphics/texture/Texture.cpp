#include "Texture.h"

#include <glew.h>

#include "../../io/image/stb_image.h"

Texture::Texture() : m_id(0), m_width(0), m_height(0), m_target(GL_TEXTURE_2D)
{
}

Texture::~Texture()
{
	cleanup();
}

void Texture::load(const char* file)
{
	init();
	bind();
	glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	
	glTexParameterf(m_target, GL_TEXTURE_MAX_ANISOTROPY_EXT, 8);

	int components = 0;
	unsigned char* data = stbi_load(file, &m_width, &m_height, &components, 4);
	glTexImage2D(m_target, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	glGenerateMipmap(m_target);
	stbi_image_free(data);
	unbind();
}

void Texture::init()
{
	glGenTextures(1, &m_id);
}

void Texture::cleanup()
{
	if (m_id != 0) {
		glDeleteTextures(1, &m_id);
		m_id = 0;
	}
}

void Texture::bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(m_target, m_id);
}

void Texture::unbind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(m_target, 0);
}