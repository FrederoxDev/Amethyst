#include "minecraft/src/common/world/item/ItemStack.hpp"

ItemStack::ItemStack() : ItemStackBase() {
    this->vtable = reinterpret_cast<uintptr_t**>(SlideAddress(0x53F5CF8));
}