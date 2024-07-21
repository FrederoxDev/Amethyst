#pragma once
#include <optional>
#include <amethyst/Memory.hpp>
#include <minecraft/src-deps/core/utility/NonOwnerPointer.hpp>
#include <minecraft/src-deps/core/resource/ResourceHelper.hpp>
#include <minecraft/src-deps/minecraftrenderer/renderer/TextureGroupBase.hpp>
#include <minecraft/src-deps/minecraftrenderer/renderer/BedrockTexture.hpp>
#include <minecraft/src-deps/coregraphics/TextureSetLayerTypes.hpp>
#include <minecraft/src-client/common/client/renderer/TexturePtr.hpp>

namespace cg { class ImageBuffer; }

namespace mce {
	class TextureContainer;

	class TextureGroup : public Bedrock::EnableNonOwnerReferences, public TextureGroupBase {
	public:
        /* this + 48  */ std::byte padding48[352];
        /* this + 400 */ std::map<ResourceLocation, BedrockTexture> mLoadedTextures;

		BedrockTexture& uploadTexture(const ResourceLocation& resource, const mce::TextureContainer& texture, std::optional<std::string_view> debugName);
        BedrockTexture& uploadTexture(const ResourceLocation& resource, cg::ImageBuffer imageBuffer);

		// 1.21.0.3 - 48 89 5C 24 ? 57 48 83 EC ? 48 8B 99 ? ? ? ? 48 8B F9 48 8B 1B 80 7B ? ? 75 ? 0F 1F 00 48 8D 53
        void unloadAllTextures();
	};
}

// 1.21.0.3
//static_assert(offsetof(mce::TextureGroup, mLoadedTextures) == 376);