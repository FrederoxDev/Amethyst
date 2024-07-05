#pragma once
#include <minecraft/src/common/gamerefs/gamerefs_shareptr/GameRefsSharePtr.hpp>

template <typename Traits>
class OwnerPtrT : public Traits::OwnerStorage {
private:
    using OwnerStackRef = typename Traits::OwnerStackRef;

public:
    OwnerPtrT(std::nullptr_t) {
        this->_getShared() = std::make_shared<Traits::StackRef>();
    }

    /*OwnerPtrT(const std::shared_ptr<Traits::StackRef>& shared) {
        this->_getShared() = shared;
    }*/

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