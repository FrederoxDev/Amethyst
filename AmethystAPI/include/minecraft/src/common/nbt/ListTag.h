#pragma once

#include "common/nbt/Tag.h"

#include <memory>
#include <vector>

class CompoundTag;

class ListTag : public Tag {
public:
    std::vector<std::unique_ptr<Tag>> mList;
    Tag::Type mType;

    int size() const;
    Tag* get(int index) const;

    const CompoundTag* getCompound(size_t index) const;
};