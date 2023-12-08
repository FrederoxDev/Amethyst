#pragma once
#include <stdint.h>
#include "minecraft/src/common/SharedPtr.h"

class Item;

class ItemStackBase {
private:
    uintptr_t** vtable;

public:
    WeakPtr<Item> mItem;
    void* mUserData;
};