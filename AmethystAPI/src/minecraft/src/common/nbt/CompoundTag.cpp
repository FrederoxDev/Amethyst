#include "common/nbt/Tag.h"
#include "common/nbt/ByteTag.h"
#include "common/nbt/CompoundTag.h"
#include "common/nbt/CompoundTagVariant.h"

const Tag* CompoundTag::get(std::string_view name) const
{
    auto it = mTags.find(name);
    if (it != mTags.end()) {
        return it->second.get();
    }

    return nullptr;
}

template <typename T>
const T* CompoundTag::get(std::string_view name) const
{
    auto it = mTags.find(name);
    if (it != mTags.end()) {
        return it->second.get<T>();
    }

    return nullptr;
}

template <typename T>
T* CompoundTag::get(std::string_view name)
{
    auto it = mTags.find(name);
    if (it != mTags.end()) {
        return it->second.get<T>();
    }

    return nullptr;
}

Tag* CompoundTag::get(std::string_view name)
{
    auto it = mTags.find(name);
    if (it != mTags.end()) {
        return it->second.get();
    }

    return nullptr;
}

bool CompoundTag::contains(std::string_view name) const
{
    return get(name) != nullptr;
}

bool CompoundTag::contains(std::string_view name, Tag::Type type) const
{
    const Tag* tag = get(name);
    if (tag) {
        return tag->getId() == type;
    }

    return false;
}

const ListTag* CompoundTag::getList(std::string_view name) const
{
    return get<ListTag>(name);
}

ListTag* CompoundTag::getList(std::string_view name)
{
    return get<ListTag>(name);
}

const ByteTag* CompoundTag::getByteTag(std::string_view name) const
{
    return get<ByteTag>(name);
}

ByteTag* CompoundTag::getByteTag(std::string_view name)
{
    return get<ByteTag>(name);
}

uint8_t CompoundTag::getByte(std::string_view name) const
{
    auto tag = getByteTag(name);
    if (tag) return tag->data;
    return 0;
}

void CompoundTag::putByte(std::string name, unsigned char value)
{
    ByteTag stringTag(value);
    mTags[name].emplace<ByteTag>(stringTag);
}

const StringTag* CompoundTag::getStringTag(std::string_view name) const
{
    return get<StringTag>(name);
}

StringTag* CompoundTag::getStringTag(std::string_view name)
{
    return get<StringTag>(name);
}

const std::string* CompoundTag::getString(std::string_view name) const
{
    auto tag = getStringTag(name);
    if (tag) {
        return &tag->data;
    }
    else {
        return nullptr;
    }
}

void CompoundTag::putString(std::string name, std::string value) {
    StringTag stringTag(value);
    mTags[name].emplace<StringTag>(stringTag);
}