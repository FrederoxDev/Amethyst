#pragma once
#include <cstddef>
#include <minecraft/src-deps/core/utility/NonOwnerPointer.hpp>

class ILevel;

class ServerNetworkHandler {
public:
    std::byte padding0[88];
    Bedrock::NonOwnerPointer<ILevel> mLevel;
};