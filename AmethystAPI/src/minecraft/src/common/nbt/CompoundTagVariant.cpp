#include "minecraft/src/common/nbt/CompoundTagVariant.h"

const Tag* CompoundTagVariant::get() const
{
    return std::visit([](const auto& tag) -> const Tag* {
        return &tag;
    },
                      mTagStorage);
}

Tag* CompoundTagVariant::get()
{
    return std::visit([](auto& tag) -> Tag* {
        return &tag;
    },
                      mTagStorage);
}

const Tag& CompoundTagVariant::operator*() const
{
    return *get();
}

Tag& CompoundTagVariant::operator*()
{
    return *get();
}

template <typename T, typename... Type>
T& CompoundTagVariant::emplace(Type&&... args)
{
    return mTagStorage.emplace<T>(std::forward<Type>(args)...);
}

template <typename T>
const T* CompoundTagVariant::get() const
{
    auto tag = std::get_if<T>(&mTagStorage);

    if (tag) {
        return tag;
    }
    else {
        return nullptr;
    }
}

template <typename T>
T* CompoundTagVariant::get()
{
    auto tag = std::get_if<T>(&mTagStorage);

    if (tag) {
        return tag;
    }
    else {
        return nullptr;
    }
}

template ListTag* CompoundTagVariant::get<ListTag>();