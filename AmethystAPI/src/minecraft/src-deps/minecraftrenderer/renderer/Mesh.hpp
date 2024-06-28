#pragma once
#include "minecraft/src-deps/minecraftrenderer/renderer/MaterialPtr.hpp"
#include "minecraft/src-deps/minecraftrenderer/renderer/MeshContext.hpp"
#include "minecraft/src-client/common/client/renderer/TexturePtr.hpp"
#include "minecraft/src-deps/minecraftrenderer/renderer/BedrockTexture.hpp"
#include <cstddef>
#include <cstdint>
#include <variant>

namespace mce {
    class Mesh {
    public:
        std::byte padding0[536];

    public:
        void renderMesh(mce::MeshContext* meshContext, const mce::MaterialPtr* materialPtr);
        void renderMesh(mce::MeshContext& meshContext, const mce::MaterialPtr& materialPtr, const std::variant<std::monostate, mce::TexturePtr, mce::ClientTexture, mce::ServerTexture>& texture);
    };

    static_assert(sizeof(Mesh) == 536);
}

