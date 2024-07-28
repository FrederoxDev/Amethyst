#pragma once

// Allocates a contiguous span of memory non owned memory
template <typename T>
class buffer_span_mut {
public:
    T* mBegin;
    T* mEnd;

    buffer_span_mut() : mBegin(nullptr), mEnd(nullptr) {}

    buffer_span_mut(T* begin, T* end) : mBegin(begin), mEnd(end) {}
};