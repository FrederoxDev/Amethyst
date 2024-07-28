#pragma once
#include <cstddef>
#include <memory>

namespace mce {
    class ClientTexture {
        std::byte padding0[32];
    };

    class ServerTexture {
        std::byte padding0[32];
    };
}

struct BedrockTextureData {
    mce::ClientTexture mClientTexture;
};

class BedrockTexture {
public:
    std::shared_ptr<BedrockTextureData> mBedrockTextureData;
};