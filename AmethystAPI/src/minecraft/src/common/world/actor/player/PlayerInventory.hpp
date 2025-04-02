#pragma once
#include <functional>
#include "minecraft/src/common/world/item/ItemStack.hpp"

class Container;
class Inventory;
class HudContainerManagerModel;

// This is probably wrong in some way or outdated, from china
enum ContainerID : unsigned char {
    CONTAINER_ID_NONE = 0xff,
    CONTAINER_ID_INVENTORY = 0x0000,
    CONTAINER_ID_FIRST = 0x0001,
    CONTAINER_ID_LAST = 0x0064,
    CONTAINER_ID_OFFHAND = 0x0077,
    CONTAINER_ID_ARMOR = 0x0078,
    CONTAINER_ID_SELECTION_SLOTS = 0x007a,
    CONTAINER_ID_PLAYER_ONLY_UI = 0x007c,
};

// yes these two funcs come before the destructors

class ContainerSizeChangeListener {
    virtual void containerSizeChanged(int);
    virtual ~ContainerSizeChangeListener() = default;
};

class ContainerContentChangeListener {
    virtual void containerContentChanged(int); 
    virtual ~ContainerContentChangeListener() = default;
};

class PlayerInventory : public ContainerSizeChangeListener, public ContainerContentChangeListener {
public:
    class SlotData {
    public:
        ContainerID mContainerId;
        int32_t mSlot;
    };

public:
    int32_t mSelected;
    ItemStack mInfiniteItem;
    ContainerID mSelectedContainerId;
    std::unique_ptr<Inventory> mInventory;
    std::vector<ItemStack> mComplexItems;
    std::weak_ptr<HudContainerManagerModel> mHudContainerManager;

    virtual ~PlayerInventory();
    virtual void createTransactionContext(
        std::function<void __cdecl(Container&, int, ItemStack const&, ItemStack const&)> callback,
        std::function<void __cdecl(void)> execute
    );

    const ItemStack& getSelectedItem() const;
};

//static_assert(offsetof(PlayerInventory, mInventory) == 224);