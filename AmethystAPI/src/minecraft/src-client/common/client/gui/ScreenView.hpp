#pragma once
#include <cstddef>

class MinecraftUIRenderContext;
using UIRenderContext = MinecraftUIRenderContext;
class VisualTree;

class ScreenView {
public:
    /* this + 0  */ float mLastTime;
    /* this + 4  */ float mTickTime;
    /* this + 8  */ std::byte padding[72 - 8];
    /* this + 72 */ VisualTree* visualTree;

    // 1.21.0.3 - 48 8B C4 48 89 58 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 70 ? 0F 29 78 ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4C 8B FA
    void setupAndRender(UIRenderContext&);
};
