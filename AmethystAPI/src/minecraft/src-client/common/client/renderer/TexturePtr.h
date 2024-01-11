#pragma once
#include "minecraft/src-deps/core/resource/ResourceHelper.h"
#include <memory>

class BedrockTextureData;

namespace mce {
class TexturePtr {
    std::shared_ptr<const BedrockTextureData> mClientTexture;
    ResourceLocation mResourceLocation;
};
} // namespace mce