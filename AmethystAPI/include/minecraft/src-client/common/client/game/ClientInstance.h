#pragma once
#include <stdint.h>
#include "minecraft/src/common/world/level/BlockSource.h"
#include "minecraft/src-client/common/client/player/LocalPlayer.h"

class ClientInstance {
private:
    uintptr_t** vtable;

public:
    // 48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 81 EC ? ? ? ? 49 8B F8 0F B6 DA
    typedef int64_t(__thiscall* _onStartJoinGame)(ClientInstance*, int64_t, int64_t, int64_t);

    BlockSource* getRegion();
    LocalPlayer* getLocalPlayer();
};