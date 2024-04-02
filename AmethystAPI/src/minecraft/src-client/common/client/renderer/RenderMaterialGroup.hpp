#pragma once
#include <amethyst/Memory.hpp>

#include "minecraft/src-deps/renderer/RenderMaterialGroupBase.hpp"

namespace mce {
    class RenderMaterialGroup {
    public:
        // 1.20.51.1 - 0x572BBB0
        // Found in ItemInHandRenderer::initMaterials
        static RenderMaterialGroupBase* switchable;
    };
};