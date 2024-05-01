#include "minecraft/src/common/world/item/ItemStackBase.hpp"

//std::string ItemStackBase::getRawNameId() const
//{
//    using function = decltype(&ItemStackBase::getRawNameId);
//
//    // known outdated for 1.20.71
//    static auto func = std::bit_cast<function>(
//        SigScan("48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 48 89 54 24 ? 57 48 83 EC ? 48 8B FA 48 8B E9 33 F6"));
//
//    return (this->*func)();
//}

void ItemStackBase::_loadItem(const CompoundTag* a1) {
    using function = decltype(&ItemStackBase::_loadItem);

    static auto func = std::bit_cast<function>(
        SigScan("48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4C 8B EA 48 89 4C 24")
    );

    (this->*func)(a1);
}

void ItemStackBase::reinit(const Item& item, int count, int auxValue)
{
    using function = void(ItemStackBase::*)(const Item&, int, int);
    auto func = std::bit_cast<function>(vtable[1]);
    (this->*func)(item, count, auxValue);
}

void ItemStackBase::reinit(const BlockLegacy& block, int count)
{
    using function = void (ItemStackBase::*)(const BlockLegacy&, int);
    auto func = std::bit_cast<function>(vtable[2]);
    (this->*func)(block, count);
}

void ItemStackBase::reinit(std::string_view name, int count, int auxValue)
{
    using function = void (ItemStackBase::*)(std::string_view, int, int);
    auto func = std::bit_cast<function>(vtable[3]);
    (this->*func)(name, count, auxValue);
}

void ItemStackBase::setNull(std::optional<std::string> reason)
{
    using function = void(ItemStackBase::*)(std::optional<std::string>);
    auto func = std::bit_cast<function>(vtable[4]);
    (this->*func)(reason);
}

std::string ItemStackBase::toString() const
{
    using function = std::string(ItemStackBase::*)() const;
    auto func = std::bit_cast<function>(vtable[5]);
    return (this->*func)();
}

std::string ItemStackBase::toDebugString() const
{
    using function = std::string(ItemStackBase::*)() const;
    auto func = std::bit_cast<function>(vtable[6]);
    return (this->*func)();
}

ItemStackBase::ItemStackBase() {
    static uintptr_t itemStackBaseVtable = AddressFromLeaInstruction(
        SigScan("4C 8D 35 ?? ?? ?? ?? 4C 89 74 24 ?? 48 89 74 24 ?? 48 89 74 24")
    );

    this->vtable = reinterpret_cast<uintptr_t**>(itemStackBaseVtable);
    this->mUserData = nullptr;
    this->mBlock = nullptr;
    this->mAuxValue = 0b1000000000000000;
    this->mCount = 0;
    this->mValid = false;
    this->mShowPickup = true;
    this->mCanPlaceOnHash = 0;
    this->mCanDestroyHash = 0;
    this->mChargedItem = nullptr;
    this->setNull(std::nullopt);
}

ItemStackBase::~ItemStackBase() = default;

// 1.20.51.1 Reimplementation - Incomplete
ItemStackBase &ItemStackBase::operator=(const ItemStackBase& rhs) {
    mCount = rhs.mCount;
    mAuxValue = rhs.mAuxValue;
    mItem = rhs.mItem;
    mBlock = rhs.mBlock;
    mValid = rhs.mValid;
    mPickupTime = rhs.mPickupTime;

    /*std::unique_ptr<CompoundTag> clonedData = nullptr;

    if (rhs.mUserData) {
        clonedData = rhs.mUserData->clone();
    }*/

    // setUserData(clonedData);
    // _cloneComponents(rhs)
    return *this;
}
