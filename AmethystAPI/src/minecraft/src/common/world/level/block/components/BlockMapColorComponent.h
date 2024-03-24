#pragma once
#include "minecraft/src-deps/core/math/Color.h"
#include "minecraft/src/common/world/level/block/components/BlockComponentBase.h"

struct BlockMapColorComponent : public BlockComponentBase {
public:
    mce::Color mMapColor;
};