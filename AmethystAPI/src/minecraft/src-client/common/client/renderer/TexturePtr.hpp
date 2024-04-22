#pragma once
#include "minecraft/src-deps/core/resource/ResourceHelper.hpp"
#include <memory>

class BedrockTextureData;

namespace mce {
    class TexturePtr {
        std::byte padding0[72];
    };
} // namespace mce