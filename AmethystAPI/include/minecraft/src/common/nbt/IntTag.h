#pragma once

#include "common/nbt/Tag.h"

class IntTag : public Tag {
public:
    int32_t data;
};