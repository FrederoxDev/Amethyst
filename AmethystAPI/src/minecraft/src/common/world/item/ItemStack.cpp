#include "minecraft/src/common/world/item/ItemStack.h"

ItemStack::ItemStack() : ItemStackBase() {
    this->vtable = reinterpret_cast<uintptr_t**>(SlideAddress(0x53F5CF8));
}