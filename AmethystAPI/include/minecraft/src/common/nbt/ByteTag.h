#pragma once
#include "common/nbt/Tag.h"

class ByteTag : public Tag {
public:
    unsigned char data;

    ByteTag(unsigned char data) {
        this->data = data;
    }
};