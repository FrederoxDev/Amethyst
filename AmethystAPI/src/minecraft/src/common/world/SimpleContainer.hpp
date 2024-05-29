#pragma once
#include <minecraft/src/common/world/Container.hpp>

class SimpleContainer : public Container {
public:
    int mSize;
    std::vector<ItemStack> mItems;
};