#include <minecraft/src/common/world/level/BlockPos.hpp>

template <>
Bedrock::Result<BlockPos> ReadOnlyBinaryStream::get<BlockPos>()
{
    auto x = getSignedVarInt32().value();
    auto y = getSignedVarInt32().value();
    auto z = getSignedVarInt32().value();

    return BlockPos(x, y, z);
}

template <>
void BinaryStream::write(BlockPos vec3)
{
    writeSignedVarInt32(vec3.x);
    writeSignedVarInt32(vec3.y);
    writeSignedVarInt32(vec3.z);
}