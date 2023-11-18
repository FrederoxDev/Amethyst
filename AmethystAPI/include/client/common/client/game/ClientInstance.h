#pragma once
#include <stdint.h>
#include "minecraft/common/world/level/BlockSource.h"
#include "Log.h"
#include "Hook.h"

class ClientInstance {
private:
    uintptr_t* vftable;

public:
    BlockSource* getRegion();
};