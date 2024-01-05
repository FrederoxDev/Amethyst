#include "minecraft/src/common/nbt/CompoundTag.h"
#include "minecraft/src/common/nbt/CompoundTagVariant.h"

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

ListTag* CompoundTag::getList(std::string_view name)
{
    return get<ListTag>(name);
}