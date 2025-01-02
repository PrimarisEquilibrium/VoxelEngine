#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <stb/stb_image.h>

#include "Texture.h"


Texture::Texture(GLenum target, GLenum textureUnit)
{
    TARGET = target;

    // Generate and bind the texture
    glGenTextures(1, &ID);
    glActiveTexture(textureUnit);
    glBindTexture(target, ID);

    // Set the wrap and texture filtering options
    glTexParameteri(TARGET, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(TARGET, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(TARGET, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(TARGET, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);

    // Define texture offsets here
    textureOffsets = {
        {TextureType::Dirt, TexelOffset{0, 0}},
        {TextureType::GrassSide, TexelOffset{TILE_SIZE * 1, 0}},
        {TextureType::GrassTop, TexelOffset{TILE_SIZE * 2, 0}}
    };
}

void Texture::load(const char* filename, GLenum format) const
{
    int width, height, nrChannels;
    unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(TARGET, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(TARGET);
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data); // Free the image from memory
}

void Texture::bind() const
{
    glBindTexture(TARGET, ID);
}

TexelOffset Texture::getTexelOffset(TextureType textureType) const
{
    auto it = textureOffsets.find(textureType);
    if (it == textureOffsets.end()) {
        std::cout << "textureType not found, default TexelOffset value is given" << std::endl;
        return TexelOffset{ 0, 0 };
    };
    return it->second;
}