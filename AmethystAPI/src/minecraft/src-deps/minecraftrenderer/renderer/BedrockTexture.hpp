#pragma once
#include <cstddef>

namespace mce {
    class ClientTexture {
        std::byte padding0[16];
    };
}

struct BedrockTextureData {
    mce::ClientTexture mClientTexture;
};

class BedrockTexture {
public:
    std::shared_ptr<BedrockTextureData> mBedrockTextureData;
};