#pragma once
#include <memory>
#include "minecraft/src-deps/core/resource/ResourceHelper.h"

class BedrockTextureData;

namespace mce {
    class TexturePtr {
        std::shared_ptr<const BedrockTextureData> mClientTexture;
        ResourceLocation mResourceLocation;
    };
}