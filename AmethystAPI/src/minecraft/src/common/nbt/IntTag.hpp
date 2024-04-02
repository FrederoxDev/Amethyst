#pragma once
#include "minecraft/src/common/nbt/Tag.hpp"

class IntTag : public Tag {
public:
    int32_t data;
};