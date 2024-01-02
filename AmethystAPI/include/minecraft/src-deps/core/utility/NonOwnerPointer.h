#pragma once
#include <memory>

namespace Bedrock {
class EnableNonOwnerReferences {
public:
    struct ControlBlock {
        EnableNonOwnerReferences* ptr;

        explicit ControlBlock(EnableNonOwnerReferences* ptr) : ptr(ptr) {}
    };

private:
    std::shared_ptr<ControlBlock> controlBlock;

public:
    EnableNonOwnerReferences() : controlBlock(std::make_shared<ControlBlock>(this)) {}

    EnableNonOwnerReferences(const EnableNonOwnerReferences& other) = default;

    virtual ~EnableNonOwnerReferences() = default;

    EnableNonOwnerReferences& operator=(const EnableNonOwnerReferences& other) = default;
};

template <typename T = EnableNonOwnerReferences>
class NonOwnerPointer {
private:
    std::shared_ptr<EnableNonOwnerReferences::ControlBlock> controlBlock;

public:
    NonOwnerPointer() : controlBlock(nullptr) {}

    explicit NonOwnerPointer(T* ptr) : controlBlock(ptr->controlBlock) {}

    NonOwnerPointer(const NonOwnerPointer<T>& other) : controlBlock(other.controlBlock) {}

    NonOwnerPointer& operator=(const NonOwnerPointer<T>& other)
    {
        this->controlBlock = other.controlBlock;
        return *this;
    }

    NonOwnerPointer& operator=(T* ptr)
    {
        this->controlBlock = ptr->controlBlock;
        return *this;
    }

    T* operator->() const
    {
        return static_cast<T*>(this->controlBlock.get()->ptr);
    }

    T& operator*() const
    {
        return *this->operator->();
    }

    bool operator==(void*) const
    {
        return this->controlBlock == nullptr;
    }

    bool operator!=(void*) const
    {
        return this->controlBlock != nullptr;
    }
};

} // namespace Bedrock