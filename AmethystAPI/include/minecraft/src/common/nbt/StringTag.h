#pragma once
#include "minecraft/src/common/nbt/Tag.h"

class StringTag : public Tag {
public:
    std::string data;
};