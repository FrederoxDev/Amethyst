#pragma once
#include <cstdint>
#include <cstddef>
#include "minecraft/src-deps/minecraftrenderer/renderer/MeshContext.hpp"
#include "minecraft/src-deps/minecraftrenderer/renderer/MaterialPtr.hpp"

namespace mce {
    class Mesh {
    public:
        std::byte padding0[536];

    public:
        // 1.20.51.1 - 48 89 5C 24 ? 48 89 74 24 ? 57 48 81 EC ? ? ? ? 49 8B D8 C6 44 24
        void renderMesh(mce::MeshContext* meshContext, const mce::MaterialPtr* materialPtr);
    };

    static_assert(sizeof(Mesh) == 536);
}

