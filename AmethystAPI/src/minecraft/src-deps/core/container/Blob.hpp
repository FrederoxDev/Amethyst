#pragma once
#include <cstddef>
#include <cstdint>
#include <memory>

namespace mce {
    class Blob {
    public:
        typedef std::size_t size_type;
        typedef uint8_t value_type;
        typedef std::unique_ptr<unsigned char[]> pointer_type;
        typedef mce::Blob::value_type* iterator;

    private:
        pointer_type mBlob;
        size_type mSize;

    public:
        Blob();
        Blob(const iterator data, const size_type size);
    };
}