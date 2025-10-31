#include "hooks/ResourceHooks.hpp"

#ifdef CLIENT
void Amethyst::ResourceHooks::initializeResourceStack(
    VanillaGameModuleClient* self,
    const Experiments& experiments,
    const Bedrock::NotNullNonOwnerPtr<ResourcePackRepository>& repository,
    ResourcePackStack& stack,
    const BaseGameVersion& baseGameVer,
    GameModuleClient::ResourceLoadingPhase loadingPhase)
{
    auto& context = Amethyst::GetContext();
    context.mPackManager->AddResourcePacksToStack(repository, stack);
    _initializeResourceStack(self, experiments, repository, stack, baseGameVer, loadingPhase);
}
#endif

void Amethyst::ResourceHooks::initializeBehaviorStack(
    VanillaGameModuleServer* self,
    const Experiments& experiments,
    const Bedrock::NotNullNonOwnerPtr<ResourcePackRepository>& repository,
    ResourcePackStack& stack,
    const BaseGameVersion& baseGameVer,
    GameModuleClient::ResourceLoadingPhase loadingPhase)
{
    auto& context = Amethyst::GetContext();
    context.mPackManager->AddBehaviorPacksToStack(repository, stack);
    _initializeBehaviorStack(self, experiments, repository, stack, baseGameVer, loadingPhase);
}

void Amethyst::ResourceHooks::initializePackSource(ResourcePackRepository* self)
{
    __initializePackSource(self);
    auto& context = Amethyst::GetContext();
    auto& packManager = *context.mPackManager;
    const auto& allPacks = packManager.GetPacks();
    size_t totalSize = std::accumulate(
        allPacks.begin(), allPacks.end(), 0ull,
        [](size_t sum, const auto& pair) {
            return sum + pair.second.size(); 
        }
    );

    Log::Info("Initializing {} modded pack sources...", totalSize);

    // Add mod "resource_packs" and "behavior_packs" to the CompositePackSource
    for (auto& [nameVer, packs] : allPacks) {
        auto& platform = Amethyst::GetPlatform();
        fs::path modBasePath = platform.GetAmethystFolder() / "mods" / nameVer;

        // Check if the mod has resource packs
        bool hasResourcePacks = std::find_if(packs.begin(), packs.end(), [&](const auto& pair) {
            return pair.second.type == PackType::Resources;
        }) != packs.end();

        // Check if the mod has behavior packs
        bool hasBehaviorPacks = std::find_if(packs.begin(), packs.end(), [&](const auto& pair) {
            return pair.second.type == PackType::Behavior;
        }) != packs.end();

        // Add the resource pack source if it has resource packs
        if (hasResourcePacks) {
            auto& packSource = self->mPackSourceFactory.createDirectoryPackSource(Core::Path((modBasePath / "resource_packs").string()), PackType::Resources, PackOrigin::User, false);
            self->mPackSource->mPackSources.push_back(&packSource);
        }

        // Add the behavior pack source if it has behavior packs
        if (hasBehaviorPacks) {
            auto& packSource = self->mPackSourceFactory.createDirectoryPackSource(Core::Path((modBasePath / "behavior_packs").string()), PackType::Behavior, PackOrigin::User, false);
            self->mPackSource->mPackSources.push_back(&packSource);
        }
    }
}

void Amethyst::ResourceHooks::Create()
{
    Amethyst::HookManager& hooks = Amethyst::GetHookManager();

	#ifdef CLIENT
    hooks.CreateVirtualHook<&VanillaGameModuleClient::initializeResourceStack>(VanillaGameModuleClient::$vtable_for_this, _initializeResourceStack, &initializeResourceStack);
	#endif
	
    hooks.CreateVirtualHook<&VanillaGameModuleServer::initializeBehaviorStack>(VanillaGameModuleServer::$vtable_for_this, _initializeBehaviorStack, &initializeBehaviorStack);
    hooks.CreateDirectHook<&ResourcePackRepository::_initializePackSource>(__initializePackSource, &initializePackSource);
}