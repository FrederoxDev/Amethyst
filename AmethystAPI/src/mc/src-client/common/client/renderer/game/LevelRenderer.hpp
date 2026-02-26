/// @symbols
#pragma once
#include <amethyst/Imports.hpp>

class ScreenContext;
struct FrameRenderObject;

class LevelRenderer {
public:
	MC void renderLevel(ScreenContext& screenContext, FrameRenderObject& frameRenderObject);
};
