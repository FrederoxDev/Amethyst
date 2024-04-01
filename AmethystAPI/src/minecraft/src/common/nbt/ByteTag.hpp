#pragma once
#include "minecraft/src/common/nbt/Tag.hpp"
#include "amethyst/Memory.hpp"

class ByteTag : public Tag {
public:
    unsigned char data;

    ByteTag(unsigned char data) {
        this->data = data;
    }
};