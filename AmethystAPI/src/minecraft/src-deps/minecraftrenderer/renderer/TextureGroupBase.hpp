#pragma once
#include <memory>
#include <optional>
#include <map>
#include <minecraft/src-deps/coregraphics/TextureSetLayerTypes.hpp>
#include <minecraft/src-client/common/client/renderer/TexturePtr.hpp>
#include <minecraft/src-deps/core/utility/NonOwnerPointer.hpp>
#include <minecraft/src-deps/core/resource/ResourceHelper.hpp>
#include <minecraft/src-deps/minecraftrenderer/renderer/BedrockTexture.hpp>

namespace mce {
    class TextureGroupBase : public std::enable_shared_from_this<TextureGroupBase> {
    public:
        virtual ~TextureGroupBase();
        virtual mce::TexturePtr getTexture(const ResourceLocation& path, bool forceReload, std::optional<uint32_t> unk1, cg::TextureSetLayerType type);
    };
}