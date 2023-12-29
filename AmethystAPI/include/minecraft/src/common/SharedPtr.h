#pragma once

#include <atomic>
#include <type_traits>
#include <utility>

template <typename T>
class SharedPtr;

template <typename T>
class WeakPtr;

template <typename T>
class SharedCounter {
private:
    template <typename>
    friend class SharedPtr;
    template <typename>
    friend class WeakPtr;

    T* ptr;
    std::atomic<int> share_count;
    std::atomic<int> weak_count;

    SharedCounter(T* p) : ptr(p),
                          share_count(0),
                          weak_count(0)
    {
    }

    ~SharedCounter()
    {
    }

    void addSharedRef()
    {
        ++share_count;
    }

    void addWeakRef()
    {
        ++weak_count;
    }

    bool releaseSharedRef()
    {
        --share_count;

        if (share_count <= 0) {
            if (ptr) {
                T* tmp = ptr;
                ptr = nullptr;

                delete tmp;
            }

            if (weak_count <= 0) {
                return true;
            }
        }

        return false;
    }

    bool releaseWeakRef()
    {
        --weak_count;

        if (weak_count <= 0 && !ptr)
            return true;

        return false;
    }
};

template <typename T>
class SharedPtr {
private:
    SharedCounter<T>* pc;
    template <typename>
    friend class WeakPtr;

public:
    SharedPtr() : pc(nullptr)
    {
    }

    SharedPtr(std::nullptr_t);

    explicit SharedPtr(T* rawPtr) : pc(nullptr)
    {
        if (rawPtr) {
            pc = new SharedCounter<T>(rawPtr);
            pc->addSharedRef();
        }
    }

    SharedPtr(const SharedPtr& sp) : pc(sp.pc)
    {
        if (pc) {
            pc->addSharedRef();
        }
    }

    template <typename TDerived, typename std::enable_if<std::is_base_of<T, TDerived>::value>::type* = nullptr>
    SharedPtr(const SharedPtr<TDerived>& sp) : pc(reinterpret_cast<const SharedPtr<T>&>(sp).pc)
    {
        if (pc) {
            pc->addSharedRef();
        }
    }

    SharedPtr(const SharedCounter<T>& sp);

    ~SharedPtr()
    {
        reset();
    }

    bool isUnique() const;
    int useCount() const;
    int weakCount() const;

    bool operator==(T* p);

    T* get() const { return (pc) ? pc->ptr : nullptr; }
    operator T*() const { return get(); }
    T& operator*() const { return *pc->ptr; }
    T* operator->() const { return pc->ptr; }
    T& operator[](int) const;

    SharedPtr& operator=(const SharedPtr& other)
    {
        SharedPtr tmp(other);
        std::swap(pc, tmp.pc);
        return *this;
    }

    void reset()
    {
        if (pc) {
            if (pc->releaseSharedRef())
                delete pc;

            pc = nullptr;
        }
    }

    static const SharedPtr<T>& null();
    WeakPtr<T> createWeakPtr();

    template <typename... Args>
    static SharedPtr<T> make(Args&&... args)
    {
        return SharedPtr<T>(new T(std::forward<Args>(args)...));
    }
};

template <typename T>
class WeakPtr {
private:
    SharedCounter<T>* pc;
    template <typename>
    friend class SharedPtr;

public:
    WeakPtr() : pc(nullptr)
    {
    }

    WeakPtr(std::nullptr_t) : pc(nullptr)
    {
    }

    WeakPtr(const SharedPtr<T>& sp) : pc(sp.pc)
    {
        if (pc) {
            pc->addWeakRef();
        }
    }

    WeakPtr(const WeakPtr& wp) : pc(wp.pc)
    {
        if (pc) {
            pc->addWeakRef();
        }
    }

    template <typename TDerived, typename std::enable_if<std::is_base_of<T, TDerived>::value>::type* = nullptr>
    WeakPtr(const WeakPtr<TDerived>& sp) : pc(reinterpret_cast<const WeakPtr<T>&>(sp).pc)
    {
        if (pc) {
            pc->addWeakRef();
        }
    }

    ~WeakPtr()
    {
        reset();
    };

    WeakPtr& operator=(const WeakPtr& other)
    {
        WeakPtr<T> tmp(other);
        std::swap(pc, tmp.pc);
        return *this;
    }

    WeakPtr& operator=(const SharedPtr<T>& other)
    {
        SharedPtr<T> tmp(other);
        std::swap(pc, tmp.pc);
        return *this;
    }

    int useCount() const;
    int weakCount() const;
    bool isNull() const { return (pc) ? pc->ptr == nullptr : true; }
    bool operator==(T* p) { return (pc) ? (pc->ptr == p) : (p == nullptr); }

    T* get() const { return (pc) ? pc->ptr : nullptr; }
    operator T*() const { return get(); }
    T& operator*() const { return *pc->ptr; }
    T* operator->() const { return pc->ptr; }
    T& operator[](int) const;

    void reset()
    {
        if (pc) {
            if (pc->releaseWeakRef())
                delete pc;

            pc = nullptr;
        }
    }

    static const WeakPtr<T>& null()
    {
        static WeakPtr<T> wnull;
        return wnull;
    }
};