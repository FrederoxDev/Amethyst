/// @symbolgeneration
#pragma once
#include <amethyst/Imports.hpp>

class ScreenContext;
struct FrameRenderObject;

class LevelRenderer {
public:
	/// @signature {48 89 5C 24 ? 55 56 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 49 8B F8 48 8B DA 48 8B E9, win-client}
	MC void renderLevel(ScreenContext& screenContext, FrameRenderObject& frameRenderObject);
};
