#pragma once
#include <string>
#include <minecraft/src-deps/core/utility/Result.hpp>

class ReadOnlyBinaryStream {
private:
    size_t mReadPointer;
    bool mHasOverflowed;
    const std::string mOwnedBuffer;
    const std::string& mBuffer;

public:
    virtual ~ReadOnlyBinaryStream();
    virtual Bedrock::Result<void, std::error_code> read(void* target, uint64_t num);

public:
    Bedrock::Result<unsigned char> getUnsignedChar();
};

class BinaryStream : public ReadOnlyBinaryStream {
private:
    std::string mOwnedBuffer;
    std::string& mBuffer;

public:
    void writeUnsignedChar(unsigned char in, const char* fieldName, const char* fieldNotes);
};