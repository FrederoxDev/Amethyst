#pragma once
#include <minecraft/src-deps/core/string/StringHash.hpp>
#include <minecraft/src/common/world/level/block/BlockShape.hpp>
#include <minecraft/src-client/common/client/renderer/texture/IsotropicFaceData.hpp>
#include <minecraft/src/common/world/level/block/BlockRenderLayer.hpp>
#include <minecraft/src/common/world/level/block/Block.hpp>

class BlockGraphics {
public:
    /* this + 0  */ uintptr_t** vtable;
    /* this + 8  */ IsotropicFaceData mIsotropicFaceData;
    /* this + 16 */ const Block* mBlock;
    BlockRenderLayer mRenderLayer;
    BlockShape mBlockShape;
    bool mAnimatedTexture;
    float mBrightnessGamma;
    bool mFancy;
    bool mAllowSame;

public:
    // 1.20.71.1 - 48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 55 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 48 8B D9 45 33 E4 E8
    static void initBlocks(void*);
    static BlockGraphics createBlockGraphics(HashedString& identifier, BlockShape shape);
};