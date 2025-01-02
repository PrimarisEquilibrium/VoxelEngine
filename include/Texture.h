#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Texture
{
public:
    unsigned int ID;
    GLenum target;

    Texture(GLenum target, GLenum textureUnit);

    /* Loads the texture from file */
    void load(const char* filename, GLenum format);
    /* Binds this texture to the target state */
    void bind() const;
};

#endif