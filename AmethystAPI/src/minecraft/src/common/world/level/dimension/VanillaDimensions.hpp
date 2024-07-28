#pragma once
#include <string>
#include <minecraft/src-deps/core/utility/AutomaticID.hpp>
#include <minecraft/src-deps/core/utility/Result.hpp>
#include <minecraft/src/common/util/BiMap.hpp>

class VanillaDimensions {
public:
    static const DimensionType Overworld;
    static const DimensionType Nether;
    static const DimensionType TheEnd;
    static const DimensionType Undefined;
    static BidirectionalUnorderedMap<std::string, DimensionType>* DimensionMap;

    // 1.21.0.3 - 40 53 48 83 EC ? 4C 63 02
    static const std::string toString(const DimensionType& dimId);

    // 1.21.0.3 - 48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B DA 48 8B F9 0F B7 11
    static int toSerializedInt(const DimensionType& dimId);

    // 1.21.0.3 - 48 89 5C 24 ? 48 89 7C 24 ? 55 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 48 8B D9 48 8D 4D
    static Bedrock::Result<DimensionType> fromSerializedInt(Bedrock::Result<int>&& serializedValue);
};