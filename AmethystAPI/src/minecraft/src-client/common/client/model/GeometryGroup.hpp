#pragma once
#include <memory>
#include <unordered_map>
#include <mutex>

#include <minecraft/src-deps/core/string/StringHash.hpp>
#include <minecraft/src-client/common/client/model/GeometryInfo.hpp>
#include <minecraft/src-deps/core/utility/NonOwnerPointer.hpp>
    
class GeometryGroup : 
    public std::enable_shared_from_this<GeometryGroup>, 
    public Bedrock::EnableNonOwnerReferences 
{
public:
    /* this + 40  */ std::unordered_map<HashedString, std::shared_ptr<GeometryInfo>> mGeometries;
    /* this + 104 */ std::mutex mGeometryLock;
};

static_assert(offsetof(GeometryGroup, mGeometryLock) == 104);