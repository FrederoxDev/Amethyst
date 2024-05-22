#pragma once
#include <memory>

template <typename T>
class OwnerStorageSharePtr {
private:
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