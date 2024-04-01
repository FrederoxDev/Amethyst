#pragma once
#include "minecraft/src-deps/core/math/Color.hpp"
#include "minecraft/src/common/world/level/block/components/BlockComponentBase.hpp"

struct BlockMapColorComponent : public BlockComponentBase {
public:
    mce::Color mMapColor;
};