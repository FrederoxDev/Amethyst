#include "FillingContainer.hpp"

#include "minecraft/src/common/world/item/ItemStack.hpp"

extern "C" void* FillingContainer_vtable;

FillingContainer::FillingContainer(Player* player, int size, ContainerType type) : Container(type),
    mPlayer(player)
{
    //workaround to place the original game vtable on the class instance even in a implemented constructor
    *reinterpret_cast<void**>(this) = FillingContainer_vtable;
    mItems.resize(size);
}

// 1.21.0.3 - Re-Implemented
const ItemStack& FillingContainer::getItem(int slot) const
{
    if (slot < 0 || slot >= mItems.size())
        return ItemStack::EMPTY_ITEM;
    return mItems[slot];
}

// 1.21.0.3 - Re-Implemented
void FillingContainer::setItem(int slot, const ItemStack& item)
{
    setItemWithForceBalance(slot, item, false);
}

// 1.21.0.3 - Re-Implemented
int FillingContainer::getContainerSize() const
{
    return mItems.size();
}

// 1.21.0.3 - Re-Implemented
int FillingContainer::getMaxStackSize() const
{
    return 254;
}

// 1.21.0.3 - Re-Implemented
void FillingContainer::startOpen(Player&)
{
}
