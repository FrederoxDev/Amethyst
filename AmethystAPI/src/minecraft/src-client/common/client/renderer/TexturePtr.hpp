#pragma once
#include "minecraft/src-deps/core/resource/ResourceHelper.hpp"
#include <memory>

class BedrockTextureData;

namespace mce {
    class TexturePtr {
    public:
        std::shared_ptr<const BedrockTextureData> mClientTexture;
        std::shared_ptr<ResourceLocation> mResourceLocation;
    };
} // namespace mce