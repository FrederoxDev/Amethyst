#include "common/world/actor/Mob.h"
#include "common/world/actor/player/PlayerInventory.h"

class Player : public Mob {
public:
    bool __padding0[512];
    PlayerInventory* playerInventory; // this + 2024
    bool __padding1[5416];
};

static_assert(sizeof(Player) == 7584);