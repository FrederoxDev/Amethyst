#pragma once

#include "common/nbt/Tag.h"
#include "common/nbt/ByteTag.h"
#include "common/nbt/ListTag.h"
#include "common/nbt/StringTag.h"

#include <map>
#include <string_view>

class CompoundTagVariant;
typedef std::map<std::string, CompoundTagVariant, std::less<>> TagMap;

class CompoundTag : public Tag {
public:
    TagMap mTags;

public:
    const Tag* get(std::string_view name) const;
    Tag* get(std::string_view);

    bool contains(std::string_view name) const;
    bool contains(std::string_view name, Tag::Type type) const;

    const ListTag* getList(std::string_view name) const;
    ListTag* getList(std::string_view name);

    const ByteTag* getByteTag(std::string_view name) const;
    ByteTag* getByteTag(std::string_view name);
    uint8_t getByte(std::string_view) const;
    void putByte(std::string name, unsigned char value);

    const StringTag* getStringTag(std::string_view name) const;
    StringTag* getStringTag(std::string_view name);
    const std::string* getString(std::string_view name) const;
    void putString(std::string name, std::string value);

private:
    template <typename T>
    const T* get(std::string_view) const;

    template <typename T>
    T* get(std::string_view);
};