#pragma once
#include "amethyst/Memory.h"
#include <stdint.h>
#include <string>

class CompoundTag;
class Level;
class ItemStackBase;

#pragma pack(push, 1)
class Item {
public:
    uintptr_t** vtable;
    bool padding0[104];
    void* qword70; // this + 112
    bool padding1[24];
    void* qword90; // this + 144
    bool padding2[10];
    int16_t mId;        // this + 162
    int16_t mMaxDamage; // this + 164
    bool padding3[2];
    std::string* mItemName; // this + 168
    bool padding4[72];
    std::string mNamespace; // this + 248

public:
    // 40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 49 8B F1 4C 89 44 24 ? 4C 8B F2 48 8B D9
    typedef void(__thiscall* _appendFormattedHovertext)(Item*, const ItemStackBase&, Level&, std::string&, uint8_t);

    short getDamageValue(CompoundTag*) const;
    uint64_t getMaxDamage() const;
};
#pragma pack(pop)