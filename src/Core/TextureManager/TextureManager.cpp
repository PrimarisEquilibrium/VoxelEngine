#include "TextureManager.h"

TextureManager::TextureManager()
{
    textureOffsets = {
        {TextureType::Dirt, TexelOffset{0, 0}},
        {TextureType::GrassSide, TexelOffset{TILE_SIZE * 1, 0}},
        {TextureType::GrassTop, TexelOffset{TILE_SIZE * 2, 0}}
    };
}

TexelOffset TextureManager::getTexelOffset(TextureType textureType) const
{
    auto it = textureOffsets.find(textureType);
    if (it == textureOffsets.end()) {
        std::cout << "textureType not found, default TexelOffset value is given" << std::endl;
        return TexelOffset{ 0, 0 };
    };
    return it->second;
}