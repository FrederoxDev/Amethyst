#pragma once
#include <cstddef>

#include "minecraft/src-deps/core/string/StringHash.h"
#include "minecraft/src-client/common/client/renderer/RenderMaterialGroup.h"

namespace mce {
    class MaterialPtr {
        std::byte padding0[16];

    public:
        MaterialPtr(mce::RenderMaterialGroupBase &, const HashedString &);
    };
}