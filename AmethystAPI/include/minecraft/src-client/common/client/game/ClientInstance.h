#pragma once
#include <stdint.h>
#include "minecraft/src/common/world/level/BlockSource.h"
#include "minecraft/src-client/common/client/player/LocalPlayer.h"
#include "minecraft/src-client/common/client/game/MinecraftGame.h"

#pragma pack(push, 1)
class ClientInstance {
private:
    uintptr_t** vtable;
    bool padding0[192];
public:
    MinecraftGame& minecraftGame;

public:
    // 48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 81 EC ? ? ? ? 49 8B F8 0F B6 DA
    typedef int64_t(__thiscall* _onStartJoinGame)(ClientInstance*, int64_t, int64_t, int64_t);

    BlockSource* getRegion();
    LocalPlayer* getLocalPlayer();
};
#pragma pack(pop)