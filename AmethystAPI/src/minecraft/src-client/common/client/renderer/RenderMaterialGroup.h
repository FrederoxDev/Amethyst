#pragma once
#include <amethyst/Memory.h>

#include "minecraft/src-deps/renderer/RenderMaterialGroupBase.h"

namespace mce {
    class RenderMaterialGroup {
    public:
        // 1.20.51.1 - 0x572BBB0
        // Found in ItemInHandRenderer::initMaterials
        static RenderMaterialGroupBase* switchable;
    };
};