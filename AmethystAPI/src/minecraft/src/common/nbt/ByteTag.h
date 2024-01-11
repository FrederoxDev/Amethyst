#pragma once
#include "minecraft/src/common/nbt/Tag.h"
#include "amethyst/Memory.h"

class ByteTag : public Tag {
public:
    unsigned char data;

    ByteTag(unsigned char data) {
        this->data = data;
    }
};