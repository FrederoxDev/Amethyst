#include "minecraft/src/common/world/actor/Mob.hpp"
#include "minecraft/src/common/world/actor/player/PlayerInventory.hpp"
#include <minecraft/src/common/world/PlayerUIContainer.hpp>

class Player : public Mob {
public:
    /* this + 1648 */ std::byte padding1648[320];
    /* this + 1968 */ PlayerInventory* playerInventory;
    /* this + 1976 */ std::byte padding1976[1456];
    /* this + 3432 */ PlayerUIContainer mPlayerUIContainer;
};

static_assert(offsetof(Player, mPlayerUIContainer) == 3432);