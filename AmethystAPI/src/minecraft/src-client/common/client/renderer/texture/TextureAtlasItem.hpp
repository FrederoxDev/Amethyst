#pragma once
#include "TextureUVCoordinateSet.hpp"

class TextureAtlasItem {
public:
    std::string mName;
    std::byte padding32[8];
    std::vector<std::vector<TextureUVCoordinateSet>> mTextureUVs;
};