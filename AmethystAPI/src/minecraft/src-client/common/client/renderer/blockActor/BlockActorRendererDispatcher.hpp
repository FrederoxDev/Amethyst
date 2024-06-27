#pragma once
#include <memory>
#include <gsl/gsl>
#include <minecraft/src-deps/core/utility/NonOwnerPointer.hpp>
#include <map>

namespace mce { class TextureGroup; };
class GeometryGroup;
class BlockTessellator;
class ActorResourceDefinitionGroup;
class ResourcePackManager;
class ResourceLoadManager;
class BaseGameVersion;
class Experiments;
class MinecraftGameplayGraphicsResources;
class BlockActorRenderer;

class BlockActorRenderDispatcher {
public:
    std::map<BlockActorRendererId, std::unique_ptr<BlockActorRenderer>> mRenderers;

public:
    // 1.20.71.1 - 40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4D 8B F9 49 8B F8 48 89 55
    void initializeBlockEntityRenderers(
        const gsl::not_null<Bedrock::NonOwnerPointer<GeometryGroup>>& geometryGroup, 
        std::shared_ptr<mce::TextureGroup> textures, 
        BlockTessellator& blockTessellator, 
        const gsl::not_null<Bedrock::NonOwnerPointer<const ActorResourceDefinitionGroup>>& entityResourceDefGroup, 
        ResourcePackManager& resourcePackManager, 
        MinecraftGameplayGraphicsResources& gameplayGraphicsResources, 
        gsl::not_null<Bedrock::NonOwnerPointer<ResourceLoadManager>> resourceLoadManager, 
        const BaseGameVersion& a8, 
        const Experiments& a9
    );
};