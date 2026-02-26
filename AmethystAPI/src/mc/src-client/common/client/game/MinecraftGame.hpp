/// @symbols
#pragma once
#include <memory>
#include "amethyst/Imports.hpp"
#include <mc/src-client/common/client/renderer/TextureGroup.hpp>

class MinecraftInputHandler;
class FontRepository;
class ResourcePackRepository;
class ResourcePackManager;

class MinecraftGame {
public:
	/* this + 0    */ uintptr_t** vtable;
	/* this + 8    */ std::byte padding8[352 - 8];
	/* this + 352  */ std::shared_ptr<FontRepository> mFontRepository;
	/* this + 368  */ std::byte padding368[1920 - 1560];
	/* this + 728  */ ResourcePackManager* mResourcePackManager;
	/* this + 736  */ std::byte padding736[2088 - 736];
	/* this + 2088 */ std::shared_ptr<mce::TextureGroup> mTextures;
	/* this + 2104 */ std::byte padding2104[2272 - 2104];
	/* this + 2272 */ std::unique_ptr<ResourcePackRepository> mResourcePackRepository;
	/* this + 2280 */ std::byte padding2280[3328 - 2280];
	/* this + 3328 */ std::unique_ptr<MinecraftInputHandler> mInput;
	/* this + 3336 */ std::byte padding3336[4272 - 3336];

	MC void onActiveResourcePacksChanged(ResourcePackManager& resourcePackManager);

	MC void onAppSuspended();
};

static_assert(offsetof(MinecraftGame, mTextures) == 2088);
