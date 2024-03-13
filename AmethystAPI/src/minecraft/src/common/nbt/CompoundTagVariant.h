#pragma once
#include "minecraft/src/common/nbt/StringTag.h"
#include "minecraft/src/common/nbt/ByteArrayTag.h"
#include "minecraft/src/common/nbt/ByteTag.h"
#include "minecraft/src/common/nbt/CompoundTag.h"
#include "minecraft/src/common/nbt/DoubleTag.h"
#include "minecraft/src/common/nbt/EndTag.h"
#include "minecraft/src/common/nbt/FloatTag.h"
#include "minecraft/src/common/nbt/Int64Tag.h"
#include "minecraft/src/common/nbt/IntArrayTag.h"
#include "minecraft/src/common/nbt/IntTag.h"
#include "minecraft/src/common/nbt/ListTag.h"
#include "minecraft/src/common/nbt/ShortTag.h"
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