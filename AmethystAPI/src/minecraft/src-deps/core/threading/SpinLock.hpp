#pragma once
#include <atomic>
#include <cstdint>
#include <functional>
#include <thread>

class SpinLock {
    static const uint32_t LOOP_LIMIT_BEFORE_YIELD = 3000;
    std::hash<std::thread::id> mThreadHasher;
    const size_t mNoThreadId;
    std::atomic<size_t> mOwnerThread;
    uint32_t mOwnerRefCount;

public:
    SpinLock();
    ~SpinLock();
    bool try_lock();
    void lock();
    void unlock();

private:
    size_t _getThreadId();
    bool _try_lock(const size_t desiredId);
};