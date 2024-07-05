#pragma once
#include <cstdint>
#include <variant>

namespace mce {
    class ClientTexture;
    class ServerTexture;
    class TexturePtr;
    class MeshContext;
    class MaterialPtr;

    class Mesh {
    public:
        std::byte padding0[536];

    public:
        void renderMesh(mce::MeshContext& meshContext, const mce::MaterialPtr& materialPtr);
        void renderMesh(mce::MeshContext& meshContext, const mce::MaterialPtr& materialPtr, const std::variant<std::monostate, mce::TexturePtr, mce::ClientTexture, mce::ServerTexture>& texture);
    };

    static_assert(sizeof(Mesh) == 536);
}

