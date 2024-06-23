#pragma once
#include <minecraft/src-deps/core/utility/NonOwnerPointer.hpp>

class NetEventCallback : public Bedrock::EnableNonOwnerReferences {
public:
    virtual ~NetEventCallback();
};