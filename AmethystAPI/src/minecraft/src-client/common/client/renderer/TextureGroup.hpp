#pragma once
#include <optional>
#include <amethyst/Memory.hpp>
#include <minecraft/src-deps/core/utility/NonOwnerPointer.hpp>
#include <minecraft/src-deps/core/resource/ResourceHelper.hpp>
#include <minecraft/src-deps/minecraftrenderer/renderer/TextureGroupBase.hpp>
#include <minecraft/src-deps/minecraftrenderer/renderer/BedrockTexture.hpp>
#include <minecraft/src-deps/coregraphics/TextureSetLayerTypes.hpp>
#include <minecraft/src-client/common/client/renderer/TexturePtr.hpp>

namespace mce {
class TextureGroup : public Bedrock::EnableNonOwnerReferences, public TextureGroupBase {
    public:
        /* this + 40  */ std::byte padding40[336];
        /* this + 376 */ std::map<ResourceLocation, BedrockTexture> mLoadedTextures;

        virtual ~TextureGroup();

        // 1.21.0.3 - 40 55 53 56 57 41 54 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 45 0F B6 E1 44 88 4C 24
        virtual mce::TexturePtr getTexture(const ResourceLocation& path, bool forceReload, std::optional<uint32_t> unk1, cg::TextureSetLayerType type);
    };
}

// 1.21.0.3
static_assert(offsetof(mce::TextureGroup, mLoadedTextures) == 376);