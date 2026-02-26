/// @symbols
#pragma once
#include <cstddef>
#include <amethyst/Imports.hpp>

class MinecraftUIRenderContext;
class VisualTree;

class ScreenView {
public:
    /* this + 0  */ float mLastTime;
    /* this + 4  */ float mTickTime;
    /* this + 8  */ std::byte padding[72 - 8];
    /* this + 72 */ VisualTree* visualTree;

    MC void setupAndRender(MinecraftUIRenderContext&);
};
