#include "FillingContainer.hpp"

#include "minecraft/src/common/world/item/ItemStack.hpp"

FillingContainer::FillingContainer(Player* player, int size, ContainerType type) : Container(type),
    mPlayer(player)
{
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
    return (int)mItems.size();
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
