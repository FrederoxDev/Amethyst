#pragma once
#include "minecraft/src/common/world/actor/Mob.hpp"
#include <minecraft/src/common/world/PlayerUIContainer.hpp>
#include <minecraft/src/common/world/item/ItemGroup.hpp>

class PlayerInventory;
class ChunkSource;
class ItemStackNetManagerBase;
class PlayerEventCoordinator;
class InventoryTransaction;

#pragma pack(push, 1)
class Player : public Mob {
public:
    /* this + 1512 */ std::byte padding1512[376];
    /* this + 1888 */ PlayerInventory* playerInventory;
    /* this + 1896 */ std::byte padding1896[1400];
    /* this + 3288 */ ItemGroup mCursorSelectedItemGroup;
    /* this + 3432 */ PlayerUIContainer mPlayerUIContainer;
    /* this + 3803 */ std::byte padding3803[2648];
    /* this + 6472 */ std::unique_ptr<ItemStackNetManagerBase> mItemStackNetManager;
    /* this + 6480 */ std::byte padding6480[1112];

    /* virtuals */
    void prepareRegion(ChunkSource& cs);
    const PlayerInventory& getSupplies() const;
    const ItemStack& getSelectedItem() const;
    PlayerEventCoordinator& getPlayerEventCoordinator(); // pure virt
    void sendInventoryTransaction(const InventoryTransaction& transaction); // pure virt
};
#pragma pack(pop)


// 1.21.0.3
static_assert(offsetof(Player, mItemStackNetManager) == 6472);
static_assert(offsetof(Player, playerInventory) == 1888);
static_assert(sizeof(Player) == 7592);  


// idk version
//static_assert(offsetof(Player, mPlayerUIContainer) == 3432); 