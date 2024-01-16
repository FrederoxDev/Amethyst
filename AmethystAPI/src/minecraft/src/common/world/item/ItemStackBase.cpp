#include "common/world/item/ItemStackBase.h"

#include "amethyst/Memory.h"

std::string& ItemStackBase::getRawNameId(std::string& str) const
{
    static auto function = reinterpret_cast<_getRawNameId>(
        SigScan("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 48 89 54 24 ? 57 48 83 EC ? 48 8B FA 48 8B E9 33 F6"));

    // returns a ref to str param
    return function(this, str);
}

void ItemStackBase::_loadItem(const CompoundTag* a1) {
    using function = void(__thiscall*)(ItemStackBase*, const CompoundTag*);

    static auto func = reinterpret_cast<function>(
        SigScan("48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 48 8B F2 48 89 54 24 ? 4C 8B F9 48 89 4C 24")
    );

    func(this, a1);
}