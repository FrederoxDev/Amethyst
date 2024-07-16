#include "Blob.hpp"

mce::Blob::Blob() : mBlob(nullptr, Deleter()), mSize(0) {}

mce::Blob::Blob(const iterator data, const size_type size)
    : mBlob(data, defaultDeleter), mSize(size) {}

void mce::Blob::defaultDeleter(iterator data)
{
    delete[] data;
}
