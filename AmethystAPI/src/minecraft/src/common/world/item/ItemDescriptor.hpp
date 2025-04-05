#pragma once
#include <memory>
class Item;

class ItemDescriptor {
public:
    struct ItemEntry {
        const Item* mItem;
        short mAuxValue;
    };

    class BaseDescriptor {
    public:
        virtual std::unique_ptr<BaseDescriptor> clone() const = 0;
    };

    std::unique_ptr<BaseDescriptor> mImpl;

    virtual std::unique_ptr<BaseDescriptor> clone() const {
        using function = decltype(&ItemDescriptor::clone);
        auto func = std::bit_cast<function>(((uintptr_t**)this)[0]);
        return (this->*func)();
    };

    ItemDescriptor(const ItemDescriptor& other)
    {
        mImpl = other.mImpl->clone();
    }

    ItemDescriptor& operator=(const ItemDescriptor& other)
    {
        if (this != &other) {
            if (other.mImpl) {
                mImpl = other.mImpl->clone();
            }
            else {
                mImpl.reset();
            }
        }

        return *this;
    }

    ItemDescriptor(ItemDescriptor&& other) noexcept = default;
    ItemDescriptor& operator=(ItemDescriptor&& other) noexcept = default;
    ~ItemDescriptor() = default;
};

class InternalItemDescriptor : ItemDescriptor::BaseDescriptor {
public:
    ItemDescriptor::ItemEntry mItemEntry;
};