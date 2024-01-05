#pragma once
#include "minecraft/src/common/nbt/Tag.h"

class ByteTag : public Tag {
public:
    unsigned char data;
};