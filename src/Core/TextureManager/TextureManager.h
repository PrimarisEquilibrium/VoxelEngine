#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <unordered_map>
#include <iostream>

enum class TextureType
{
    Dirt,
    GrassSide,
    GrassTop
};

struct TexelOffset
{
    int x_offset;
    int y_offset;
};

class TextureManager
{
public:
    // How many pixels wide each tile on the texture atlas is.
    const int TILE_SIZE = 16;

    // Hashmap containing key value pairs of the texture type to texel offset.
    std::unordered_map<TextureType, TexelOffset> textureOffsets;

    /**
     * Constructor for TextureManager class.
     */
    TextureManager();

    /**
     * Returns the TexelOffset of the given texture.
     * 
     * @param textureType The texture to get the TexelOffset of.
     * @return The TexelOffset.
     */
    TexelOffset getTexelOffset(TextureType textureType) const;
};

#endif