#pragma once
#include <cstddef>

class MinecraftUIRenderContext;
using UIRenderContext = MinecraftUIRenderContext;
class VisualTree;

class ScreenView {
public:
    std::byte padding[72];
    VisualTree* visualTree; // this + 72

    // unknown - 48 8B C4 48 89 58 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 70 ? 0F 29 78 ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4C 8B FA 48 89 54 24 ? 4C 8B E9 48 89 4C 24
    void* setupAndRender(UIRenderContext*);
};
