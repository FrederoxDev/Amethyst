#pragma once
#include "minecraft/src/common/world/actor/Mob.hpp"
#include <minecraft/src/common/world/PlayerUIContainer.hpp>
#include <minecraft/src/common/world/item/ItemGroup.hpp>

class PlayerInventory;
class ChunkSource;
class ItemStackNetManagerBase;

#pragma pack(push, 1)
class Player : public Mob {
public:
    /* this + 1648 */ std::byte padding1648[240];
    /* this + 1888 */ PlayerInventory* playerInventory;
    /* this + 1896 */ std::byte padding1896[1400];
    /* this + 3288 */ ItemGroup mCursorSelectedItemGroup;
    /* this + 3432 */ PlayerUIContainer mPlayerUIContainer;
    /* this + 3803 */ std::byte padding3803[2648];
    /* this + 6472 */ std::unique_ptr<ItemStackNetManagerBase> mItemStackNetManager;

    /* virtuals */
    void prepareRegion(ChunkSource& cs);
};
#pragma pack(pop)


// 1.21.0.3
static_assert(offsetof(Player, mItemStackNetManager) == 6472);
static_assert(offsetof(Player, playerInventory) == 1888);


// idk version
//static_assert(offsetof(Player, mPlayerUIContainer) == 3432); 