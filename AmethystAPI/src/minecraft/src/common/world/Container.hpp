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

class Container {
public:
    uintptr_t** vtable;
    ContainerType mContainerType;
    ContainerType mGameplayContainerType;
    std::unordered_set<ContainerContentChangeListener*> mContentChangeListeners;
    std::unordered_set<ContainerSizeChangeListener*> mSizeChangeListeners;
    std::unordered_set<ContainerCloseListener*> mCloseListeners;
    //std::unordered_set<ContainerRemovedListener*> mRemovedListeners; // added after 1.20.71.1
    std::deque<std::function<void(Container&, int, const ItemStack&, const ItemStack&)>> mTransactionContextStack;
    std::string mName;
    bool mCustomName;
    ContainerRuntimeId mContainerRuntimeId;

//vfuncs:
    const ItemStack* getItem(int slot);
};