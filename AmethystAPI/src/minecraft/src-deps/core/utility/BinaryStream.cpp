#include "BinaryStream.hpp"
#include <minecraft/src/common/world/Facing.hpp>

template <typename T>
Bedrock::Result<T> ReadOnlyBinaryStream::get()
{
    T data{};

    auto result = read(&data, sizeof(T));
    if (!result) Assert("this->read<T>() had an exception.");

    return Bedrock::Result<T>(data);
}

template Bedrock::Result<unsigned char> ReadOnlyBinaryStream::get<unsigned char>();
template Bedrock::Result<uint64_t> ReadOnlyBinaryStream::get<uint64_t>();
template Bedrock::Result<float> ReadOnlyBinaryStream::get<float>();
template Bedrock::Result<bool> ReadOnlyBinaryStream::get<bool>();
template Bedrock::Result<FacingID> ReadOnlyBinaryStream::get<FacingID>();

Bedrock::Result<uint32_t> ReadOnlyBinaryStream::getUnsignedVarInt32()
{
    uint32_t value = 0;
    int shift = 0;

    while (true) {
        unsigned char byte;
        auto result = this->read(&byte, 1);
        if (!result) Assert("read failed");

        value |= (byte & 0x7F) << shift;
        if (!(byte & 0x80)) break;
        shift += 7;
        if (shift >= 32) Assert("out of range");
    }

    return Bedrock::Result<uint32_t>(value);
}

Bedrock::Result<int32_t> ReadOnlyBinaryStream::getSignedVarInt32()
{
    auto result = getUnsignedVarInt32();
    if (!result) Assert("Issue with reading unsigned var int");

    uint32_t value = result.value();
    return Bedrock::Result<int32_t>((value >> 1) ^ -static_cast<int32_t>(value & 1));
}

Bedrock::Result<std::string> ReadOnlyBinaryStream::getString()
{
    auto length = getUnsignedVarInt32();
    if (!length) Assert("Issue with reading string length");

    std::string value;
    value.resize(length.value());

    auto result = read(&value[0], length.value());
    if (!result) Assert("Issue with reading string");

    return Bedrock::Result<std::string>(value);
}

template <typename T>
void BinaryStream::write(T in)
{
    unsigned char* bytes = reinterpret_cast<unsigned char*>(&in);

    for (int i = 0; i < sizeof(T); i++) {
        mBuffer += bytes[i];
    }
}

template void BinaryStream::write(unsigned char);
template void BinaryStream::write(float);
template void BinaryStream::write(bool);
template void BinaryStream::write(uint64_t);
template void BinaryStream::write(FacingID);

void BinaryStream::writeUnsignedVarInt32(uint32_t value)
{
    while (value > 0x7F) {
        mBuffer += (unsigned char)((value & 0x7F) | 0x80);
        value >>= 7;
    }
    mBuffer += (unsigned char)value;
}

void BinaryStream::writeSignedVarInt32(int32_t value)
{
    writeUnsignedVarInt32((value << 1) ^ (value >> 31));
}

void BinaryStream::writeString(std::string value) {
    writeUnsignedVarInt32((uint32_t)value.size());
    mBuffer += value;
}
