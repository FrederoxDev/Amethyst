#pragma once
#include "common/nbt/StringTag.h"
#include "common/nbt/ByteArrayTag.h"
#include "common/nbt/ByteTag.h"
#include "common/nbt/CompoundTag.h"
#include "common/nbt/DoubleTag.h"
#include "common/nbt/EndTag.h"
#include "common/nbt/FloatTag.h"
#include "common/nbt/Int64Tag.h"
#include "common/nbt/IntArrayTag.h"
#include "common/nbt/IntTag.h"
#include "common/nbt/ListTag.h"
#include "common/nbt/ShortTag.h"
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