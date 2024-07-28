#pragma once
#include <cstdint>
#include <variant>
#include <minecraft/src-client/common/client/renderer/TexturePtr.hpp>
#include <minecraft/src-deps/minecraftrenderer/renderer/BedrockTexture.hpp>
#include <minecraft/src-deps/minecraftrenderer/renderer/MeshData.hpp>

namespace mce {
    class ClientTexture;
    class ServerTexture;
    class TexturePtr;
    class MeshContext;
    class MaterialPtr;

    class Mesh {
    public:
        /* this + 0   */ std::byte padding0[120];
        /* this + 120 */ mce::MeshData mMeshData;
        /* this + 392 */ std::byte padding392[536 - 392];

    public:
        void renderMesh(mce::MeshContext& meshContext, const mce::MaterialPtr& materialPtr);
        void renderMesh(mce::MeshContext& meshContext, const mce::MaterialPtr& materialPtr, const std::variant<std::monostate, mce::TexturePtr, mce::ClientTexture, mce::ServerTexture>& texture);
    };

    static_assert(sizeof(Mesh) == 536);
}

