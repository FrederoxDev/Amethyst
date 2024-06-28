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
};
}

// 1.21.0.3
static_assert(offsetof(mce::TextureGroup, mLoadedTextures) == 376);