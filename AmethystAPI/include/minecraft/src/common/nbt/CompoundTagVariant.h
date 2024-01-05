#pragma once
#include <variant>
#include "minecraft/src/common/nbt/EndTag.h"
#include "minecraft/src/common/nbt/ByteTag.h"
#include "minecraft/src/common/nbt/ShortTag.h"
#include "minecraft/src/common/nbt/IntTag.h"
#include "minecraft/src/common/nbt/Int64Tag.h"
#include "minecraft/src/common/nbt/FloatTag.h"
#include "minecraft/src/common/nbt/DoubleTag.h"
#include "minecraft/src/common/nbt/ByteArrayTag.h"
#include "minecraft/src/common/nbt/StringTag.h"
#include "minecraft/src/common/nbt/ListTag.h"
#include "minecraft/src/common/nbt/IntArrayTag.h"
#include "minecraft/src/common/nbt/CompoundTag.h"

class CompoundTagVariant {
public:
    std::variant<EndTag, ByteTag, ShortTag, IntTag, Int64Tag, FloatTag, DoubleTag, ByteArrayTag, StringTag, 
        ListTag, CompoundTag, IntArrayTag> mTagStorage;

    const Tag* get() const;

    Tag* get();

    const Tag& operator*() const;

    Tag& operator*();

    template <typename T, typename... Type>
    T& emplace(Type&&... args);

    template <typename T>
    const T* get() const;

    template <typename T>
    T* get();
};