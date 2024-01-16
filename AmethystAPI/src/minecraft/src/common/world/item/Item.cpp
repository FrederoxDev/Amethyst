#include "common/world/item/Item.h"

short Item::getDamageValue(CompoundTag* mUserData) const
{
    using function = short(__thiscall*)(const Item*, CompoundTag*);
    static auto func = reinterpret_cast<function>(SigScan("48 89 5C 24 ? 57 48 83 EC ? 48 8B DA 48 85 D2"));
    return func(this, mUserData);
}

uint64_t Item::getMaxDamage() const
{
    using function = uint64_t(__thiscall*)(const Item*);
    return reinterpret_cast<function>(this->vtable[33])(this);
}