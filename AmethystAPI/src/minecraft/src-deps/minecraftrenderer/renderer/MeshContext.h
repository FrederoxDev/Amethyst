#pragma once

#include "minecraft/src-deps/minecraftrenderer/hal/interface/RenderContext.h"
#include "minecraft/src-deps/renderer/Camera.h"

namespace mce {
    class MeshContext {
    public:
        /* this + 0  */ mce::RenderContext& renderContext;
        /* this + 9  */ std::byte padding9[16];
        /* this + 24 */ mce::Camera** camera;
        // ^^ I am not sure about what exactly this is, it might even just be an mce::Camera* directly...
        // Nothing seems right
    };
}