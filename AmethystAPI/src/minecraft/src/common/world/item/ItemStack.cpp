#include "common/world/item/ItemStack.h"

#include "amethyst/Memory.h"

ItemStack::ItemStack() {
	using function = void(__thiscall*)(ItemStack*);
    static auto func = reinterpret_cast<function>(SigScan("48 89 4C 24 ? 53 48 83 EC ? 48 8B D9 48 8D 05 ? ? ? ? 48 89 01 33 C0 48 89 41 ? 48 89 41 ? 48 89 41 ? C7 41 ? ? ? ? ? 48 89 41 ? 66 C7 41 ? ? ? 48 89 41 ? 48 89 41 ? 48 89 41 ? 48 89 41 ? 48 89 41 ? 48 89 41 ? 48 89 41 ? 48 89 41 ? 48 89 41 ? 48 89 81 ? ? ? ? 88 44 24"));
    func(this);

    // For whatever reason when this ctor is used in game,
    // the caller assigns the vtable for ItemStack over ItemStackBase
    this->vtable = reinterpret_cast<uintptr_t**>(SlideAddress(0x53C75F0)); // 1.20.51.1
}

void ItemStack::reinit(std::string_view name, int count, int auxValue) {
    using function = void(__thiscall*)(ItemStack*, std::string_view, int, int);
    reinterpret_cast<function>(this->vtable[1])(this, name, count, auxValue);
}

void ItemStack::reinit(const Item* item, int count, int auxValue)
{
    using function = void(__thiscall*)(ItemStack*, const Item*, int, int);
    reinterpret_cast<function>(this->vtable[3])(this, item, count, auxValue);
}