#pragma once
#include "minecraft/src/common/nbt/Tag.hpp"
#include "amethyst/Memory.hpp"

class StringTag : public Tag {
public:
    std::string data;

    StringTag(std::string data) {
        this->data = data;
    }
};