#pragma once
#include <minecraft/src/common/gamerefs/gamerefs_shareptr/GameRefsSharePtr.hpp>

template <typename Traits>
class OwnerPtrT : public Traits::OwnerStorage {
public:
    using OwnerStackRef = typename Traits::OwnerStackRef;

    OwnerStackRef& operator*() const {
        return *(this->_getShared());
    }

    OwnerStackRef* operator->() const
    {
        return this->_getShared().get();
    }
};

template <typename T>
using OwnerPtr = OwnerPtrT<SharePtrRefTraits<T>>;