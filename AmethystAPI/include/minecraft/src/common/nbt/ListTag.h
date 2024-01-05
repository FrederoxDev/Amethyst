#pragma once
#include "minecraft/src/common/nbt/Tag.h"
#include <vector>
#include <memory>

class ListTag : public Tag {
public:
    std::vector<std::unique_ptr<Tag>> mList;
    Tag::Type mType;
};