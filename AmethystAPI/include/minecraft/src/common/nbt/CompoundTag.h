#pragma once
#include "minecraft/src/common/nbt/Tag.h"
#include <map>
#include <string_view>

class CompoundTagVariant;
typedef std::map<std::string, CompoundTagVariant, std::less<>> TagMap;

class ListTag;

class CompoundTag : public Tag {
public:
    TagMap mTags;

public:
    const Tag* get(std::string_view name) const;
    Tag* get(std::string_view);

    bool contains(std::string_view name) const;
    bool contains(std::string_view name, Tag::Type type) const;

    ListTag* getList(std::string_view name);

private:
    template <typename T>
    const T* get(std::string_view) const;

    template <typename T>
    T* get(std::string_view);
};