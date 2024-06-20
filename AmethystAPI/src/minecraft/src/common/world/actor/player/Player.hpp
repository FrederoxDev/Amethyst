#include "minecraft/src/common/world/actor/Mob.hpp"
#include "minecraft/src/common/world/actor/player/PlayerInventory.hpp"
#include <minecraft/src/common/world/PlayerUIContainer.hpp>
#include <minecraft/src/common/world/item/ItemGroup.hpp>

class Player : public Mob {
public:
    /* this + 1648 */ std::byte padding1648[320];
    /* this + 1968 */ PlayerInventory* playerInventory;
    /* this + 1976 */ std::byte padding1976[1312];
    /* this + 3288 */ ItemGroup mCursorSelectedItemGroup;
    /* this + 3432 */ PlayerUIContainer mPlayerUIContainer;
};

static_assert(offsetof(Player, mPlayerUIContainer) == 3432); 