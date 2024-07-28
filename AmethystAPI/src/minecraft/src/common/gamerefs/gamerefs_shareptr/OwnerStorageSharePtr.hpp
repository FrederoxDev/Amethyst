#pragma once
#include <memory>
#include <cstddef>

template <typename T>
class OwnerStorageSharePtr {
public:
    std::shared_ptr<T> mValue;

protected:
    bool _hasValue() const;
    void _reset();

    std::shared_ptr<T> _getShared() const {
        return mValue;
    }

    T& _getStackRef() const {
        return *mValue.get();
    }
};