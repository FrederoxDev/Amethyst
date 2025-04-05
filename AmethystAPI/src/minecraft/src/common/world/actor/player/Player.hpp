#pragma once
#include <memory>
#include "minecraft/src/common/world/actor/Mob.hpp"
#include <minecraft/src/common/world/PlayerUIContainer.hpp>
#include <minecraft/src/common/world/item/ItemGroup.hpp>
#include <minecraft/src/common/world/inventory/transaction/InventoryTransactionManager.hpp>

class PlayerInventory;
class ChunkSource;
class ItemStackNetManagerBase;
class PlayerEventCoordinator;
class InventoryTransaction;
class ComplexInventoryTransaction;
class GameMode;

#pragma pack(push, 1)
class Player : public Mob {
public:
    /* this + 1512 */ std::byte padding1512[376];
    /* this + 1888 */ PlayerInventory* playerInventory;
    /* this + 1896 */ std::byte padding1896[1400];
    /* this + 3288 */ ItemGroup mCursorSelectedItemGroup;
    ///* this + 3432 */ PlayerUIContainer mPlayerUIContainer;
    /* this + 3440 */ std::byte padding3440[296];
    /* this + 3736 */ InventoryTransactionManager mTransactionManager;
    /* this + 3784 */ std::unique_ptr<GameMode> mGameMode;
    /* this + 3792 */ std::byte padding3792[2680];
    /* this + 6472 */ std::unique_ptr<ItemStackNetManagerBase> mItemStackNetManager;
    /* this + 6480 */ std::byte padding6480[1112];

    /* virtuals */
    void prepareRegion(ChunkSource& cs);
    const PlayerInventory& getSupplies() const;
    const ItemStack& getSelectedItem() const;
    PlayerEventCoordinator& getPlayerEventCoordinator(); 

    void sendInventoryTransaction(const InventoryTransaction& transaction); 
    void sendComplexInventoryTransaction(std::unique_ptr<ComplexInventoryTransaction>) const; 
};
#pragma pack(pop)


// 1.21.0.3
static_assert(offsetof(Player, mItemStackNetManager) == 6472);
static_assert(offsetof(Player, playerInventory) == 1888);
static_assert(offsetof(Player, mTransactionManager) == 3736);
static_assert(sizeof(Player) == 7592);  


// idk version
//static_assert(offsetof(Player, mPlayerUIContainer) == 3432); 