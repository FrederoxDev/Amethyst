#pragma once
#include <stdint.h>

class ItemStack;

class Container {
public:
    uintptr_t** vtable;

//vfuncs:
    const ItemStack* getItem(int slot);
};