#include "minecraft/src/common/world/actor/Mob.h"
#include "minecraft/src/common/world/actor/player/PlayerInventory.h"

class Player : public Mob {
public:
    bool padding[1304];
    PlayerInventory playerInventory; // this + 2024
};