#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <unordered_map>


enum class TextureType
{
    Dirt,
    GrassSide,
    GrassTop
};

struct TexelOffset
{
    float x_offset;
    float y_offset;
};

class Texture
{
public:
    // The ID/handler of the texture.
    GLuint ID;

    // The texture target (e.g., GL_TEXTURE_2D, GL_TEXTURE_3D)
    GLenum TARGET;

    // How many pixels wide each tile on the texture atlas is.
    const float TILE_SIZE = 16.0f;

    // Hashmap containing key value pairs of the texture type to texel offset.
    std::unordered_map<TextureType, TexelOffset> textureOffsets;

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

    /**
     * Returns the TexelOffset of the given texture.
     *
     * @param textureType The texture to get the TexelOffset of.
     * @return The TexelOffset.
     */
    TexelOffset getTexelOffset(TextureType textureType) const;
};

#endif