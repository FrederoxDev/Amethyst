#pragma once

#include "minecraft/src-deps/minecraftrenderer/hal/interface/RenderContext.hpp"
#include "minecraft/src-deps/renderer/Camera.hpp"


#pragma pack(push, 1)
namespace mce {
    class MeshContext {
    public:
        /* this + 0  */ mce::RenderContext& renderContext;
        /* this + 8  */ mce::Camera* camera;
    };
}
#pragma pack(pop)