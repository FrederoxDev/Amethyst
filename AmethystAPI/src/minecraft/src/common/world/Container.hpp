#pragma once
#include <cstdint>
#include <unordered_set>
#include <deque>
#include <string>
#include <functional>

class ItemStack;
class ContainerContentChangeListener;
class ContainerSizeChangeListener;
class ContainerCloseListener;
class ContainerRemovedListener;

enum class ContainerType : signed char {
    NONE = -9, 
    INVENTORY = -1, 
    CONTAINER, 
    WORKBENCH, 
    FURNACE, 
    ENCHANTMENT, 
    BREWING_STAND, 
    ANVIL, 
    DISPENSER, 
    DROPPER, 
    HOPPER, 
    CAULDRON, 
    MINECART_CHEST, 
    MINECART_HOPPER, 
    HORSE, 
    BEACON, 
    STRUCTURE_EDITOR, 
    TRADE, 
    COMMAND_BLOCK, 
    JUKEBOX, 
    ARMOR, 
    HAND, 
    COMPOUND_CREATOR, 
    ELEMENT_CONSTRUCTOR, 
    MATERIAL_REDUCER, 
    LAB_TABLE, 
    LOOM, 
    LECTERN, 
    GRINDSTONE, 
    BLAST_FURNACE, 
    SMOKER, 
    STONECUTTER, 
    CARTOGRAPHY, 
    HUD, 
    JIGSAW_EDITOR, 
    SMITHING_TABLE, 
    CHEST_BOAT
};

// It's actually TypedRuntimeId<ContainerRuntimeIdTag, unsigned int, 0>
// mojang likes their raw type wrappers lol :p
using ContainerRuntimeId = unsigned int;

class BlockSource;
class CompoundTag;
class Player;
class Vec3;

class Container {
public:
    ContainerType mContainerType;
    ContainerType mGameplayContainerType;
    std::unordered_set<ContainerContentChangeListener*> mContentChangeListeners;
    std::unordered_set<ContainerSizeChangeListener*> mSizeChangeListeners;
    std::unordered_set<ContainerCloseListener*> mCloseListeners;
    std::unordered_set<ContainerRemovedListener*> mRemovedListeners;
    std::deque<std::function<void(Container&, int, const ItemStack&, const ItemStack&)>> mTransactionContextStack;
    std::string mName;
    bool mCustomName;
    ContainerRuntimeId mContainerRuntimeId;

public:
    Container(ContainerType type);
    Container(ContainerType type, const std::string& containerName, bool hasCustomName);
    virtual ~Container();
    
public:
    virtual void init();
    virtual void serverInitItemStackIds(int, int, std::function<void(int, const ItemStack&)>) = 0;
    virtual void addContentChangeListener(ContainerContentChangeListener*);
    virtual void removeContentChangeListener(ContainerContentChangeListener*);
    virtual void addRemovedListener(ContainerRemovedListener*);
    virtual void removeRemovedListener(ContainerRemovedListener*);
    virtual const ItemStack& getItem(int) const = 0;
    virtual bool hasRoomForItem(const ItemStack&);
    virtual void addItem(ItemStack&);
    virtual void addItemWithForceBalance(ItemStack&);
    virtual bool addItemToFirstEmptySlot(const ItemStack&);
    virtual void setItem(int, const ItemStack&) = 0;
    virtual void setItemWithForceBalance(int, const ItemStack&, bool);
    virtual void removeItem(int, int);
    virtual void removeAllItems();
    virtual void removeAllItemsWithForceBalance();
    virtual void containerRemoved();
    virtual void dropSlotContent(BlockSource&, const Vec3&, bool, int);
    virtual void dropContents(BlockSource&, const Vec3&, bool);
    virtual int getContainerSize() const = 0;
    virtual int getMaxStackSize() const = 0;
    virtual void startOpen(Player&) = 0;
    virtual void stopOpen(Player&);
    virtual std::vector<ItemStack, std::allocator<ItemStack>> getSlotCopies() const;
    virtual const std::vector<ItemStack const *,std::allocator<ItemStack const*>> getSlots() const;
    virtual int getEmptySlotsCount() const;
    virtual int getItemCount(const ItemStack&);
    virtual int findFirstSlotForItem(const ItemStack&) const;
    virtual bool canPushInItem(int, int, const ItemStack&) const;
    virtual bool canPullOutItem(int, int, const ItemStack&) const;
    virtual void setContainerChanged(int);
    virtual void setContainerMoved();
    virtual void setCustomName(const std::string& name);
    virtual bool hasCustomName() const;
    virtual void readAdditionalSaveData(const CompoundTag&);
    virtual void addAdditionalSaveData(CompoundTag&);
    virtual void createTransactionContext(std::function<void (Container&, int, ItemStack const&, ItemStack const&)>, std::function<void()>);
    virtual void initializeContainerContents(BlockSource&);
    virtual bool isEmpty() const;
    virtual bool isSlotDisabled(int slot);
    virtual bool hasGetStrictParsingVersion();
};

// 1.21.0.3
static_assert(sizeof(Container) == 352);