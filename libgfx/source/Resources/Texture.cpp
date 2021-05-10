#include "Resources/Texture.h"
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <glad/glad.h>

namespace Resources
{
	TemporaryTexture::TemporaryTexture(const char* filename, int* width, int* height, int* comp, int req_comp)
	{
		m_pixels = stbi_load(filename, width, height, comp, req_comp);
	}

	TemporaryTexture::~TemporaryTexture()
	{
		stbi_image_free(m_pixels);
	}

	Texture::Texture(const char* filename, bool invert)
	{
		
		int m_width, m_height, m_nrChannels;

		/*Sampler c pour plusieur texture*/
		GLuint sampler = 0;
		glGenSamplers(1, &sampler);
		glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glSamplerParameteri(sampler, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4);

		GLint max = 0;
		glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &max);

		glBindSampler(0, sampler);

		glCreateTextures(GL_TEXTURE_2D, 1, &m_ID);
		stbi_set_flip_vertically_on_load(invert);
		unsigned char* data = stbi_load(filename, &m_width, &m_height, &m_nrChannels, 0);
		if (data)
		{
			glTextureParameteri(m_ID, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
			glTextureParameteri(m_ID, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

			//Filtering
			glTextureParameteri(m_ID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTextureParameteri(m_ID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			int format = (m_nrChannels == 3 ? GL_RGB8 : GL_RGBA8);
			glTextureStorage2D(m_ID, 4, format, m_width, m_height);

			format = (m_nrChannels == 3 ? GL_RGB : GL_RGBA);
			glTextureSubImage2D(m_ID, 0, 0, 0, m_width, m_height, format, GL_UNSIGNED_BYTE, data);
			glGenerateTextureMipmap(m_ID);
		}
		else
		{
			std::cerr << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);
	}

	unsigned int Texture::GetID() const
	{
		return m_ID;
	}

}
