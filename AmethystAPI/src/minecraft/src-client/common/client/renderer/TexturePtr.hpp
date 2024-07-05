#pragma once
#include <memory>

struct BedrockTextureData;
class ResourceLocation;

namespace mce {
    class TexturePtr {
    public:
        std::shared_ptr<const BedrockTextureData> mClientTexture;
        std::shared_ptr<ResourceLocation> mResourceLocation;
    };
} // namespace mce