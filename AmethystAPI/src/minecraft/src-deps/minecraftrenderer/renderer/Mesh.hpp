#pragma once
#include "minecraft/src-deps/minecraftrenderer/renderer/MaterialPtr.hpp"
#include "minecraft/src-deps/minecraftrenderer/renderer/MeshContext.hpp"
#include "minecraft/src-client/common/client/renderer/TexturePtr.hpp"
#include <cstddef>
#include <cstdint>
#include <variant>

namespace mce {
    class Mesh {
    public:
        std::byte padding0[536];

    public:
        // 1.20.51.1 - 48 89 5C 24 ? 48 89 74 24 ? 57 48 81 EC ? ? ? ? 49 8B D8 C6 44 24
        void renderMesh(mce::MeshContext* meshContext, const mce::MaterialPtr* materialPtr);
        void renderMesh(mce::MeshContext* meshContext, const mce::MaterialPtr* materialPtr, const std::variant<std::monostate, mce::TexturePtr>* texture);
    };

    static_assert(sizeof(Mesh) == 536);
}

