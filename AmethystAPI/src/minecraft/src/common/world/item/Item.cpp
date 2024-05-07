#include "minecraft/src/common/world/item/Item.hpp"

#pragma warning(push)
#pragma warning(disable : 26495)
Item::Item(const std::string& stringId, short numericalId)
{
    // 1.20.71.1
    using function = Item*(__thiscall*)(Item*, const std::string&, short);
    static auto func = reinterpret_cast<function>(SigScan("48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 55 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 41 0F B7 D8"));
    func(this, stringId, numericalId);
}
#pragma warning(pop)

short Item::getDamageValue(CompoundTag* userData) const
{
    if (userData == nullptr) return 0;
    if (!userData->contains("Damage")) return 0;
    return (short)userData->getInt("Damage");
}

Item::~Item() {

}

void Item::addCreativeItem(ItemRegistryRef* a1, const Block* a2)
{
    using function = void(*)(ItemRegistryRef*, const Block*);
    static auto func = reinterpret_cast<function>(SigScan("48 89 4C 24 ? 53 48 81 EC ? ? ? ? 48 8B D9 45 33 C9"));
    func(a1, a2);
}

const std::string& Item::getRawNameId() const {
    return mRawNameId.getString();
}

//
//uint64_t Item::getMaxDamage() const
//{
//    using function = uint64_t(__thiscall*)(const Item*);
//    return reinterpret_cast<function>(this->vtable[33])(this);
// }