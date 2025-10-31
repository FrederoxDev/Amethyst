/// @symbolgeneration
#pragma once

#include <cstdint>
#include "mc/src-client/common/client/renderer/game/LevelRendererPlayer.hpp"
#include "mc/src/common/AppPlatformListener.hpp"
#include "mc/src/common/world/level/LevelListener.hpp"
#include "mc/src-deps/core/utility/AutomaticID.hpp"
#include <amethyst/Imports.hpp>

class ScreenContext;
struct FrameRenderObject;
class RenderChunkCoordinator;
class LevelRenderer : public LevelListener, public AppPlatformListener {
public:
    /* this + 24  */ std::unordered_map<DimensionType, std::unique_ptr<RenderChunkCoordinator>> mRenderChunkCoordinators;
    /* this + 88  */ std::byte padding88[776 - 88];
    /* this + 776 */ LevelRendererPlayer* mLevelRendererPlayer; 

    /// @signature {48 89 5C 24 ? 55 56 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 49 8B F8 48 8B DA 48 8B E9, win-client}
    MC void renderLevel(ScreenContext& screenContext, FrameRenderObject& frameRenderObject);
};