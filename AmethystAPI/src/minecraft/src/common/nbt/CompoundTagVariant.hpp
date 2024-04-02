#pragma once
#include "minecraft/src/common/nbt/StringTag.hpp"
#include "minecraft/src/common/nbt/ByteArrayTag.hpp"
#include "minecraft/src/common/nbt/ByteTag.hpp"
#include "minecraft/src/common/nbt/CompoundTag.hpp"
#include "minecraft/src/common/nbt/DoubleTag.hpp"
#include "minecraft/src/common/nbt/EndTag.hpp"
#include "minecraft/src/common/nbt/FloatTag.hpp"
#include "minecraft/src/common/nbt/Int64Tag.hpp"
#include "minecraft/src/common/nbt/IntArrayTag.hpp"
#include "minecraft/src/common/nbt/IntTag.hpp"
#include "minecraft/src/common/nbt/ListTag.hpp"
#include "minecraft/src/common/nbt/ShortTag.hpp"
#include <variant>

class CompoundTagVariant {
    typedef std::variant<EndTag, ByteTag, ShortTag, IntTag, Int64Tag, FloatTag, DoubleTag, ByteArrayTag, StringTag, ListTag, CompoundTag, IntArrayTag> Variant;

public:
    Variant mTagStorage;

    CompoundTagVariant() {}
    CompoundTagVariant(CompoundTagVariant&&) = default;
    CompoundTagVariant(const CompoundTagVariant&) = delete;
    CompoundTagVariant(Tag&&);
    CompoundTagVariant& operator=(CompoundTagVariant&&) = default;
    CompoundTagVariant& operator=(const CompoundTagVariant&) = delete;
    Tag& emplace(Tag&&);

    CompoundTagVariant copy() const
    {
        return std::visit([](const auto& tag) {
            return CompoundTagVariant(std::move(*tag.copy()));
        },
        mTagStorage);
    }

    const Tag* operator->() const
    {
        return get();
    }

    Tag* operator->()
    {
        return get();
    }

    const Tag* get() const
    {
        return std::visit([](const auto& tag) -> const Tag* {
            return &tag;
        },
        mTagStorage);
    }

    Tag* get()
    {
        return std::visit([](auto& tag) -> Tag* {
            return &tag;
        },
        mTagStorage);
    }

    const Tag& operator*() const
    {
        return *get();
    }

    Tag& operator*()
    {
        return *get();
    }

    template <typename T, typename... Type>
    T& emplace(Type&&... args)
    {
        return mTagStorage.emplace<T>(std::forward<Type>(args)...);
    }

    template <typename T>
    const T* get() const
    {
        auto tag = std::get_if<T>(&mTagStorage);
        if (!tag) return nullptr;
        return tag;
    }

    template <typename T>
    T* get()
    {
        auto tag = std::get_if<T>(&mTagStorage);
        if (!tag) return nullptr;
        return tag;
    }
};