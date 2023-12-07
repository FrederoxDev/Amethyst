#pragma once
#include <stdint.h>
#include "minecraft/common/SharedPtr.h"

class Item;

class ItemStackBase {
private:
    uintptr_t** vtable;

public:
    WeakPtr<Item> mItem;
    void* mTest;
};