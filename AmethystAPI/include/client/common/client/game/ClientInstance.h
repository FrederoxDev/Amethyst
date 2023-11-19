#pragma once
#include <stdint.h>
#include "minecraft/common/world/level/BlockSource.h"
#include "client/common/client/player/LocalPlayer.h"

class ClientInstance {
private:
    uintptr_t** vtable;

public:
    BlockSource* getRegion();
    LocalPlayer* getLocalPlayer();
};