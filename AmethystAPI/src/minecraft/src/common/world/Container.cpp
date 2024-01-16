#include "common/world/Container.h"

const ItemStack* Container::getItem(int slot) {
    using function = const ItemStack*(__thiscall*)(Container*, int);
    return reinterpret_cast<function>(this->vtable[5])(this, slot);
}