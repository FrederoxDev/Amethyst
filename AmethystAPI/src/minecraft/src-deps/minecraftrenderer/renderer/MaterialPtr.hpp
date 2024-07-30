#pragma once
#include <cstddef>

#include "minecraft/src-deps/core/string/StringHash.hpp"
#include "minecraft/src-client/common/client/renderer/RenderMaterialGroup.hpp"

namespace mce {
    class RenderMaterialInfo : public std::enable_shared_from_this<RenderMaterialInfo> {
    public:
        HashedString mHashedName;

        RenderMaterialInfo(const HashedString& name);
    };

    class MaterialPtr {
    public:
        std::shared_ptr<RenderMaterialInfo> mRenderMaterialInfoPtr;
     
     // error LNK2005
    // public:
   // MaterialPtr(mce::RenderMaterialGroupBase& materialGroup, const HashedString& materialName);
    };
}