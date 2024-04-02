#pragma once
#include "minecraft/src/common/nbt/Tag.hpp"

class ShortTag : public Tag {
public:
    int16_t data;
};