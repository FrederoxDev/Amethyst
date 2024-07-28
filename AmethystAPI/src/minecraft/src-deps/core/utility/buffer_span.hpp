#pragma once
// Mojang why is this  the only thing in snake case
template<typename T>
class buffer_span {
public:
    T const* mBegin; // this+0x0
    T const* mEnd;   // this+0x8

    buffer_span() = default;
    buffer_span(T* begin, T* end) : mBegin(begin), mEnd(end) {}

    inline size_t size() const { return mEnd - mBegin; }

    inline T* begin() { return mBegin; }

    inline T* end() { return mEnd; }

    inline T& operator[](size_t index) { return mBegin[index]; }

    inline T const& operator[](size_t index) const { return mBegin[index]; }
};