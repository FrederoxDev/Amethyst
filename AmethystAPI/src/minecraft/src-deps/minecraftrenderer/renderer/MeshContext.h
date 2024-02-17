#pragma once

#include "minecraft/src-deps/minecraftrenderer/hal/interface/RenderContext.h"

namespace mce {
    class MeshContext {
    public:
        mce::RenderContext& renderContext;
    };
}