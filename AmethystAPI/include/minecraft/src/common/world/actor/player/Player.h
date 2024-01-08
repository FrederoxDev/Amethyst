#include "minecraft/src/common/world/actor/Mob.h"
#include "minecraft/src/common/world/actor/player/PlayerInventory.h"

class Player : public Mob {
public:
    bool __padding0[2160];
    PlayerInventory* playerInventory; // this + 3808
    bool __padding1[3768];
};

static_assert(sizeof(Player) == 7584);