#pragma once
#include <cstdint>

#include "minecraft/src-client/common/client/renderer/game/LevelRendererPlayer.hpp"

class ScreenContext;
class FrameRenderObject;

class LevelRenderer {
public:
    std::byte padding[0x308];
    LevelRendererPlayer* mLevelRendererPlayer;

    // 1.20.51.1 - 48 89 5C 24 ? 48 89 74 24 ? 55 57 41 56 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 49 8B F0 48 8B DA 4C 8B F1
    void* renderLevel(ScreenContext* screenContext, FrameRenderObject* frameRenderObject);
};