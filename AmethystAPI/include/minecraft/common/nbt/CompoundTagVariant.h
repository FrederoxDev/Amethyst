#pragma once
#include "minecraft/common/nbt/StringTag.h"
#include "minecraft/common/nbt/ByteArrayTag.h"
#include "minecraft/common/nbt/ByteTag.h"
#include "minecraft/common/nbt/CompoundTag.h"
#include "minecraft/common/nbt/DoubleTag.h"
#include "minecraft/common/nbt/EndTag.h"
#include "minecraft/common/nbt/FloatTag.h"
#include "minecraft/common/nbt/Int64Tag.h"
#include "minecraft/common/nbt/IntArrayTag.h"
#include "minecraft/common/nbt/IntTag.h"
#include "minecraft/common/nbt/ListTag.h"
#include "minecraft/common/nbt/ShortTag.h"
#include <variant>

class CompoundTagVariant {
public:
    std::variant<EndTag, ByteTag, ShortTag, IntTag, Int64Tag, FloatTag, DoubleTag, ByteArrayTag, StringTag,
                 ListTag, CompoundTag, IntArrayTag> mTagStorage;

public:
    const Tag* get() const
    {
        return std::visit([](const auto& tag) -> const Tag* {
            return &tag;
        }, mTagStorage);
    }

    Tag* get()
    {
        return std::visit([](auto& tag) -> Tag* {
            return &tag;
        }, mTagStorage);
    }

    template <typename T>
    const T* get() const
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
    T* get()
    {
        auto tag = std::get_if<T>(&mTagStorage);

        if (tag) {
            return tag;
        }
        else {
            return nullptr;
        }
    }

    template <typename T, typename... Args>
    void emplace(Args&&... args)
    {
        mTagStorage.emplace<T>(std::forward<Args>(args)...);
    }
};