#include <minecraft/src-deps/core/threading/SpinLock.hpp>

SpinLock::SpinLock() : mNoThreadId(mThreadHasher({})),
                       mOwnerRefCount(0)
{
    mOwnerThread.exchange(mNoThreadId);
}

SpinLock::~SpinLock()
{
}

bool SpinLock::try_lock()
{
    return _try_lock(_getThreadId());
}

void SpinLock::lock()
{
    size_t localThread = _getThreadId();
    uint32_t loopCount = LOOP_LIMIT_BEFORE_YIELD;

    while (!_try_lock(localThread)) {
        if (loopCount != 0) {
            --loopCount;
        }
        else {
            std::this_thread::yield();
        }
    }
}

void SpinLock::unlock()
{
    if (mOwnerThread != _getThreadId() || !mOwnerRefCount)
        throw std::errc::operation_not_permitted;

    if (mOwnerRefCount == 1) {
        mOwnerRefCount = 0;
        mOwnerThread.store(mNoThreadId, std::memory_order_release);
    }
    else {
        --mOwnerRefCount;
    }
}

size_t SpinLock::_getThreadId()
{
    return mThreadHasher(std::this_thread::get_id());
}

bool SpinLock::_try_lock(const size_t desiredId)
{
    size_t prevID = mNoThreadId;
    bool result = mOwnerThread.compare_exchange_strong(prevID, desiredId, std::memory_order_acquire);
    if (result) {
        mOwnerRefCount = 1;
        return true;
    }
    else if (prevID == desiredId && mOwnerRefCount == -2) {
        ++mOwnerRefCount;
        return true;
    }

    return false;
}