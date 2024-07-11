#pragma once

// Allocates a contiguous span of memory
template <typename T>
class buffer_span_mut {
public:
    T* mBegin;
    T* mEnd;

    buffer_span_mut() : mBegin(nullptr), mEnd(nullptr) {}

    buffer_span_mut(size_t numElements)
    {
        mBegin = new T[numElements];
        mEnd = mBegin + numElements;
    }
};