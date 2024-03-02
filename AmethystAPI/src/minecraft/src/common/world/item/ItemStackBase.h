#pragma once
#include "amethyst/Memory.h"
#include "minecraft/src/common/SharedPtr.h"
#include "minecraft/src/common/world/level/Tick.h"
#include <cstdint>
#include <string>
#include <optional>

class Item;
class CompoundTag;
class BlockLegacy;
class Block;
class ItemInstance;

class ItemStackBase {
public:
    /* this + 8   */ WeakPtr<Item> mItem;
    /* this + 16  */ CompoundTag* mUserData;
    /* this + 24  */ const Block* mBlock;
    /* this + 32  */ byte mCount;
    /* this + 33  */ std::byte padding33[15];
    /* this + 48  */ bool mShowPickup;
    /* this + 49  */ std::byte padding49[7];
    /* this + 56  */ std::vector<const BlockLegacy*> mCanPlaceOn;
    /* this + 80  */ size_t mCanPlaceOnHash;
    /* this + 88  */ std::vector<const BlockLegacy*> mCanDestroy;
    /* this + 112 */ size_t mCanDestroyHash;
    /* this + 120 */ Tick mBlockingTick;
    /* this + 128 */ std::unique_ptr<ItemInstance> mChargedItem;

public:
    virtual ~ItemStackBase();
    virtual void reinit(const Item& item, int count, int auxValue);
    virtual void reinit(const BlockLegacy& block, int count);
    virtual void reinit(std::string_view name, int count, int auxValue);
    virtual void setNull(std::optional<std::string> reason);
    virtual std::string toString() const;
    virtual std::string toDebugString() const;

public:
    // 1.20.51.1 - 48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 48 89 54 24 ? 57 48 83 EC ? 48 8B FA 48 8B E9 33 F6
    std::string getRawNameId() const;

    // 1.20.51.1 - 48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 48 8B F2 48 89 54 24 ? 4C 8B F9 48 89 4C 24
    void _loadItem(const CompoundTag*);
};

static_assert(sizeof(ItemStackBase) == 0x88);

// ItemInstance inherits from ItemStackBase but is also used as a member variable
#include "minecraft/src/common/world/item/ItemInstance.h"