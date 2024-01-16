#include "common/nbt/ListTag.h"

int ListTag::size() const {
    return (int)mList.size();
}

Tag* ListTag::get(int index) const
{
    if (index >= size()) {
        return nullptr;
    }
    else {
        return mList[index].get();
    }
}

const CompoundTag* ListTag::getCompound(size_t index) const
{
    if (index < mList.size()) {
        auto& tag = mList[index];
        if (tag->getId() == Type::Compound) {
            return reinterpret_cast<const CompoundTag*>(tag.get());
        }
    }

    return nullptr;
}