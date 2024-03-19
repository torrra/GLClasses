#include "glad/glad.h"

#define STB_IMAGE_IMPLEMENTATION
#include "STB/stb_image.h"

#include "Texture.h"

namespace ngl
{
    Texture::Texture(const char* filePath)
    {
        glCreateTextures(GL_TEXTURE_2D, 1, &m_id);

        int texWidth, texHeight, nbChannels;

        stbi_set_flip_vertically_on_load(true);

        unsigned char* textureData = stbi_load(filePath, &texWidth, &texHeight, &nbChannels, 0);

        if (textureData)
        {
            // Allocate data for image
            glTextureStorage2D(m_id, 4, GL_RGB8, texWidth, texHeight);

            // Feed data
            glTextureSubImage2D(m_id, 0, 0, 0, texWidth, texHeight, GL_RGB, GL_UNSIGNED_BYTE, textureData);
            glGenerateTextureMipmap(m_id);

            stbi_image_free(textureData);
        }

    }

    Texture::Texture(const unsigned char* pixels, int width, int height)
    {
        if (pixels)
        {
            glCreateTextures(GL_TEXTURE_2D, 1, &m_id);

            // Allocate data for image
            glTextureStorage2D(m_id, 4, GL_RGB8, width, height);

            // Feed data
            glTextureSubImage2D(m_id, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels);
            glGenerateTextureMipmap(m_id);
        }
    }

    void Texture::SetParameter(unsigned int param, unsigned int value) const
    {
        glTextureParameteri(m_id, param, value);
    }

    void Texture::SetParameter(unsigned int param, float value) const
    {
        glTextureParameterf(m_id, param, value);
    }

    void Texture::BindToUnit(unsigned int textureUnit, const Sampler& sampler) const
    {
        // Bind sampler and texture units
        glBindTextureUnit(textureUnit, m_id);
        glBindSampler(textureUnit, sampler.m_id);
    }

    Sampler::Sampler()
    {
        // Create sampler
        glCreateSamplers(1, &m_id);

        // Equivalent to glTexParameteri
        glSamplerParameteri(m_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glSamplerParameteri(m_id, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glSamplerParameteri(m_id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glSamplerParameteri(m_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    }

    void Sampler::SetParameter(unsigned int param, int value)
    {
        glSamplerParameteri(m_id, param, value);
    }

    void Sampler::SetParameter(unsigned int param, float value)
    {
        glSamplerParameterf(m_id, param, value);
    }

}
