#pragma once
#include <cstdint>

#include "minecraft/src-client/common/client/renderer/game/LevelRendererPlayer.h"

class LevelRenderer {
public:
    std::byte padding[0x308];
    LevelRendererPlayer* mLevelRendererPlayer;
};