#include "minecraft/src/common/world/Container.hpp"

// 1.21.0.3 - Re-Implemented
void Container::init()
{
}

// 1.21.0.3 - Re-Implemented
void Container::setItemWithForceBalance(int slot, const ItemStack& stack, bool)
{
    setItem(slot, stack);
}

// 1.21.0.3 - Re-Implemented
bool Container::canPushInItem(int, int, const ItemStack&) const
{
    return true;
}

// 1.21.0.3 - Re-Implemented
bool Container::canPullOutItem(int, int, const ItemStack&) const
{
    return true;
}

// 1.21.0.3 - Re-Implemented
void Container::setCustomName(const std::string& name)
{
    mCustomName = true;
    mName = name;
}

// 1.21.0.3 - Re-Implemented
bool Container::hasCustomName() const
{
    return mCustomName;
}

// 1.21.0.3 - Re-Implemented
void Container::initializeContainerContents(BlockSource&)
{
}

// 1.21.0.3 - Re-Implemented
bool Container::isSlotDisabled(int slot)
{
    return false;
}

// 1.21.0.3 - Re-Implemented
bool Container::hasGetStrictParsingVersion()
{
    return false;
}


