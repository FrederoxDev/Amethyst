#pragma once
#include "minecraft/src/common/world/actor/player/Player.hpp"
#include <cstdint>

class LocalPlayer : public Player {
public:
    // 1.21.0.3 - 48 89 5C 24 ? 57 48 83 EC ? 48 8B 01 0F B6 DA BA
    void setSprinting(bool isSprinting);
};