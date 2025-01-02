#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Texture
{
public:
    // The ID/handler of the texture.
    GLuint ID;

    // The texture target (e.g., GL_TEXTURE_2D, GL_TEXTURE_3D)
    GLenum TARGET;

    /**
     * Constructor generates the texture.
     * 
     * @param target The texture target (e.g., GL_TEXTURE_2D, GL_TEXTURE_3D).
     * @param textureUnit The assigned texture unit for the texture.
     */
    Texture(GLenum target, GLenum textureUnit);

    /**
     * Loads a texture from a file.
     *
     * @param filename The path to the texture file to be loaded.
     * @param format The texture format of the input file (e.g., GL_RGB, GL_RGBA).
     */
    void load(const char* filename, GLenum format) const;

    // Binds this texture to the target state
    void bind() const;
};

#endif