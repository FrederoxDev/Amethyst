#pragma once
#include "minecraft/src/common/nbt/Tag.h"
#include "amethyst/Memory.h"

class StringTag : public Tag {
public:
    std::string data;

    StringTag(std::string data) {
        this->data = data;
    }
};