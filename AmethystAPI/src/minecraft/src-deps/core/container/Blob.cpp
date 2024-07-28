#include "Blob.hpp"

mce::Blob::Blob() : mBlob(nullptr, Deleter()), mSize(0) {}

mce::Blob::Blob(const iterator data, const size_type size)
    : mBlob(new value_type[size], defaultDeleter), mSize(size)
{
    std::copy(data, data + size, mBlob.get());
}

mce::Blob::Blob(const Blob& other)
    : mSize(other.mSize), mBlob(nullptr, Deleter(other.mBlob.get_deleter().getDeleteFunc()))
{
    if (other.mBlob) {
        value_type* newData = new value_type[other.mSize];
        std::copy(other.mBlob.get(), other.mBlob.get() + other.mSize, newData);
        mBlob.reset(newData);
    }
}

mce::Blob::size_type mce::Blob::size() const
{
    return mSize;
}

void mce::Blob::defaultDeleter(iterator data)
{
    delete[] data;
}
