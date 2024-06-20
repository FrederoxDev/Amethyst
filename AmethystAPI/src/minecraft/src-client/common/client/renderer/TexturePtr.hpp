#pragma once
#include "minecraft/src-deps/core/resource/ResourceHelper.hpp"
#include <memory>

class BedrockTextureData;

namespace mce {
    class TexturePtr {
    public:
        std::byte padding0[4000];
    };
} // namespace mce