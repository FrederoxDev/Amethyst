#pragma once
#include "minecraft/src/common/nbt/Tag.hpp"

class StringTag : public Tag {
public:
    std::string data;

    StringTag(std::string data) {
        this->data = data;
    }
};