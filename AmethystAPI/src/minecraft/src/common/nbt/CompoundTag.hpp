#pragma once
#include "minecraft/src/common/nbt/Tag.hpp"
#include "minecraft/src/common/nbt/ByteTag.hpp"
#include "minecraft/src/common/nbt/ListTag.hpp"
#include "minecraft/src/common/nbt/StringTag.hpp"
#include "minecraft/src/common/nbt/IntTag.hpp"
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

    void clear();
    void deepCopy(const CompoundTag& other);
    std::unique_ptr<CompoundTag> clone() const;

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

    const IntTag* getIntTag(std::string_view name) const;
    IntTag* getIntTag(std::string_view name);
    int getInt(std::string_view name) const;

private:
    template <typename T>
    const T* get(std::string_view) const;

    template <typename T>
    T* get(std::string_view);
};