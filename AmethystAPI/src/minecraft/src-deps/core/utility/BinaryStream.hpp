#pragma once
#include <string>
#include <minecraft/src-deps/core/utility/Result.hpp>
#include <amethyst/Log.hpp>

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
    template <typename T>
    Bedrock::Result<T> get();

    Bedrock::Result<uint32_t> getUnsignedVarInt32();
    Bedrock::Result<int32_t> getSignedVarInt32();
    Bedrock::Result<std::string> getString();
};

extern template Bedrock::Result<unsigned char> ReadOnlyBinaryStream::get<unsigned char>();
extern template Bedrock::Result<float> ReadOnlyBinaryStream::get<float>();
extern template Bedrock::Result<bool> ReadOnlyBinaryStream::get<bool>();

class BinaryStream : public ReadOnlyBinaryStream {
private:
    std::string mOwnedBuffer;
    std::string& mBuffer;

public:
    template <typename T>
    void write(T in);

    void writeUnsignedVarInt32(uint32_t value);
    //void writeUnsignedVarInt64(uint64_t value);
    void writeSignedVarInt32(int32_t value);
    //void writeSignedVarInt64(int64_t value);

    void writeString(std::string value);
};

extern template void BinaryStream::write(unsigned char);
extern template void BinaryStream::write(float);
extern template void BinaryStream::write(bool);
extern template void BinaryStream::write(short);