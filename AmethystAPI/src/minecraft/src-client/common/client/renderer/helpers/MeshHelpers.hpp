#pragma once

#include "minecraft/src-client/common/client/renderer/Tessellator.hpp"

class ScreenContext;

namespace MeshHelpers {
    static void renderMeshImmediately(ScreenContext* screenContext, Tessellator* tessellator, const mce::MaterialPtr* material)
    {
        using function = void(*)(ScreenContext*, Tessellator*, const mce::MaterialPtr*);
        static auto func = reinterpret_cast<function>(SigScan("48 89 5C 24 ? 48 89 74 24 ? 57 48 81 EC ? ? ? ? 49 8B F8 48 8B DA 48 8B F1 80 BA"));
        func(screenContext, tessellator, material);
    }
};