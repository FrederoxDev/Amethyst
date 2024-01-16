#pragma once
#include "common/nbt/Tag.h"

class StringTag : public Tag {
public:
    std::string data;

    StringTag(std::string data) {
        this->data = data;
    }
};