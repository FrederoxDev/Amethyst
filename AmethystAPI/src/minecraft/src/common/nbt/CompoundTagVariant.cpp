#include "minecraft/src/common/nbt/CompoundTagVariant.hpp"

CompoundTagVariant::CompoundTagVariant(Tag&& tag)
{
    emplace(std::move(tag));
}

Tag& CompoundTagVariant::emplace(Tag&& tag)
{
    switch (tag.getId()) {
    case Tag::Type::End:
        return emplace<EndTag>(reinterpret_cast<EndTag&&>(tag));

    case Tag::Type::Byte:
        return emplace<ByteTag>(reinterpret_cast<ByteTag&&>(tag));

    case Tag::Type::Short:
        return emplace<ShortTag>(reinterpret_cast<ShortTag&&>(tag));

    case Tag::Type::Int:
        return emplace<IntTag>(reinterpret_cast<IntTag&&>(tag));

    case Tag::Type::Int64:
        return emplace<Int64Tag>(reinterpret_cast<Int64Tag&&>(tag));

    case Tag::Type::Float:
        return emplace<FloatTag>(reinterpret_cast<FloatTag&&>(tag));

    case Tag::Type::Double:
        return emplace<DoubleTag>(reinterpret_cast<DoubleTag&&>(tag));

    case Tag::Type::ByteArray:
        return emplace<ByteArrayTag>(reinterpret_cast<ByteArrayTag&&>(tag));

    case Tag::Type::String:
        return emplace<StringTag>(reinterpret_cast<StringTag&&>(tag));

    case Tag::Type::List:
        return emplace<ListTag>(reinterpret_cast<ListTag&&>(tag));

    case Tag::Type::Compound:
        return emplace<CompoundTag>(reinterpret_cast<CompoundTag&&>(tag));

    case Tag::Type::IntArray:
        return emplace<IntArrayTag>(reinterpret_cast<IntArrayTag&&>(tag));

    default:
        return emplace<EndTag>();
    }
}