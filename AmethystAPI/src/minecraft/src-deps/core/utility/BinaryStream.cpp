#include "BinaryStream.hpp"

Bedrock::Result<unsigned char> ReadOnlyBinaryStream::getUnsignedChar()
{
    unsigned char data = 0;
    auto result = this->read(&data, 1);

    if (!result) {
        throw std::exception("this->read() resulted in has_exception");
    }

    return Bedrock::Result<unsigned char>(data);
}

void BinaryStream::writeUnsignedChar(unsigned char in, const char* fieldName, const char* fieldNotes)
{
    mBuffer += in;
}