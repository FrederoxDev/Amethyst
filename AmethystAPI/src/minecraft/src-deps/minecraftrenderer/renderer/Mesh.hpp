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
        void renderMesh(mce::MeshContext* meshContext, const mce::MaterialPtr* materialPtr);
    };

    static_assert(sizeof(Mesh) == 536);
}

