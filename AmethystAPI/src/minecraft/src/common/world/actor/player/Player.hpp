#include "minecraft/src/common/world/actor/Mob.hpp"
#include "minecraft/src/common/world/actor/player/PlayerInventory.hpp"

class Player : public Mob {
public:
    std::byte __padding0[512];
    PlayerInventory* playerInventory; // this + 2024
    std::byte __padding1[5416];
};

static_assert(sizeof(Player) == 7584);