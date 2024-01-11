#pragma once
#include "minecraft/src/common/nbt/Tag.h"

class ShortTag : public Tag {
public:
    int16_t data;
};