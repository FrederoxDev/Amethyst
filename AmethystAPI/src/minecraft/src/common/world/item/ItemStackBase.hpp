#pragma once
#include "amethyst/Memory.hpp"
#include "minecraft/src/common/SharedPtr.hpp"
#include "minecraft/src/common/world/level/Tick.hpp"
#include <cstdint>
#include <string>
#include <optional>
#include <chrono>
#include "minecraft/src/common/nbt/CompoundTag.hpp"

class Item;
class CompoundTag;
class BlockLegacy;
class Block;
class ItemInstance;

//is_virtual = True
//    hide_vtable = True
//        struct_size = 0x88
//
//#(Type, Name, Size(in bytes), Offset(in bytes))
//    struct
//    = [("WeakPtr<Item>", "mItem", 8, 8),
//       ("CompoundTag*", "mUserData", 8, 16),
//       ("short", "mAuxValue", 2, 32),
//       ("byte", "mCount", 1, 34),
//       ("bool", "mShowPickup", 1, 48),
//       ("const Block*", "mBlock", 8, 24),
//       ("std::vector<const BlockLegacy*>", "mCanPlaceOn", 24, 56),
//       ("std::vector<const BlockLegacy*>", "mCanDestroy", 24, 88),
//       ("std::unique_ptr<ItemInstance>", "mChargedItem", 8, 128),
//       ("size_t", "mCanPlaceOnHash", 8, 80),
//       ("Tick", "mBlockingTick", 8, 120),
//       ("size_t", "mCanDestroyHash", 8, 112),
//       ("std::chrono::steady_clock::time_point", "mPickupTime", 8, 40)]

class ItemStackBase {
public:
    /* this + 0   */ uintptr_t** vtable;
    /* this + 8   */ WeakPtr<Item> mItem;
    /* this + 16  */ CompoundTag* mUserData;
    /* this + 24  */ const Block* mBlock;
    /* this + 32  */ unsigned short mAuxValue;
    /* this + 34  */ byte mCount;
    /* this + 35  */ bool mValid;
    /* this + 40  */ std::chrono::steady_clock::time_point mPickupTime;
    /* this + 48  */ bool mShowPickup;
    /* this + 56  */ std::vector<const BlockLegacy*> mCanPlaceOn;
    /* this + 80  */ size_t mCanPlaceOnHash;
    /* this + 88  */ std::vector<const BlockLegacy*> mCanDestroy;
    /* this + 112 */ size_t mCanDestroyHash;
    /* this + 120 */ Tick mBlockingTick;
    /* this + 128 */ std::unique_ptr<ItemInstance> mChargedItem;

public:
    /* Virtuals */
    ~ItemStackBase();
    void reinit(const Item& item, int count, int auxValue);
    void reinit(const BlockLegacy& block, int count);
    void reinit(std::string_view name, int count, int auxValue);
    void setNull(std::optional<std::string> reason);
    std::string toString() const;
    std::string toDebugString() const;

public:
    ItemStackBase();
    ItemStackBase& operator=(const ItemStackBase&);

    // 1.20.51.1 - 48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 48 89 54 24 ? 57 48 83 EC ? 48 8B FA 48 8B E9 33 F6
    // std::string getRawNameId() const;

    // 1.20.71.1 - 48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4C 8B EA 48 89 4C 24
    void _loadItem(const CompoundTag*);
};

static_assert(sizeof(ItemStackBase) == 0x88);

// ItemInstance inherits from ItemStackBase but is also used as a member variable
#include "minecraft/src/common/world/item/ItemInstance.hpp"