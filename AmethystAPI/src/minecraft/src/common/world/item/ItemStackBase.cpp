#include "minecraft/src/common/world/item/ItemStackBase.h"

std::string& ItemStackBase::getRawNameId(std::string& str) const
{
    static auto function = reinterpret_cast<_getRawNameId>(
        SigScan("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 48 89 54 24 ? 57 48 83 EC ? 48 8B FA 48 8B E9 33 F6"));

    // returns a ref to str param
    return function(this, str);
}