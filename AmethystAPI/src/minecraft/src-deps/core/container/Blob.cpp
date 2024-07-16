#include "Blob.hpp"

mce::Blob::Blob() 
    : mSize(0), mBlob(std::make_unique<unsigned char[]>(0)) {}

mce::Blob::Blob(const iterator data, const size_type size)
    : mSize(size), mBlob(std::make_unique<unsigned char[]>(size))
{
    if (data && size > 0) {
        std::memcpy(mBlob.get(), data, size);
    }
}