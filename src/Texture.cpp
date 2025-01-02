#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <stb/stb_image.h>

#include "../include/Texture.h"


Texture::Texture(GLenum targetTexture, GLenum textureUnit)
{
    Texture::target = targetTexture;
    glGenTextures(1, &ID);
    glActiveTexture(textureUnit);
    glBindTexture(target, ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);
}

void Texture::load(const char* filename, GLenum format)
{
    int width, height, nrChannels;
    unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data); // Free the image from memory
}

void Texture::bind() const
{
    glBindTexture(target, ID);
}