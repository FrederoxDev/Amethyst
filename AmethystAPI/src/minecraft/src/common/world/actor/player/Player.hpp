#include "minecraft/src/common/world/actor/Mob.hpp"
#include "minecraft/src/common/world/actor/player/PlayerInventory.hpp"

class Player : public Mob {
public:
    std::byte __padding0[320];
    PlayerInventory* playerInventory; // this + 1968
    std::byte __padding1[5608];
};

static_assert(sizeof(Player) == 7584);
//static_assert(offsetof(Player, playerInventory) == 1968);