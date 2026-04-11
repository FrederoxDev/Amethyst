#if defined(CLIENT) || defined(SERVER)
#include "hooks/shared/Resource.hpp"

#include <amethyst/runtime/utility/InlineHook.hpp>
#include <amethyst/runtime/ModContext.hpp>

// #include <server/module/VanillaGameModuleServer.hpp>
// #include <resources/VanillaInPackagePacks.hpp>
// #include <resources/RepositorySources.hpp>
// #include <resources/ResourcePackRepository.hpp>
// #include <resources/PackSourceFactory.hpp>

namespace Amethyst::SharedHooks::ResourceHooks {
	// Amethyst::InlineHook<decltype(&VanillaGameModuleServer::initializeBehaviorStack)> _VanillaGameModuleServer_initializeBehaviorStack;
	// void VanillaGameModuleServer_initializeBehaviorStack(
	// 	VanillaGameModuleServer* self,
	// 	const Experiments& experiments, 
	// 	const ::gsl::not_null<::Bedrock::NonOwnerPointer<IResourcePackRepository>>& repo, 
	// 	ResourcePackStack& stack, 
	// 	const BaseGameVersion& baseGameVersion, 
	// 	bool includeEditorPacks
	// ) {
	// 	auto& context = Amethyst::GetContext();
	// 	context.mPackManager->AddBehaviorPacksToStack(repo, stack);
	// 	_VanillaGameModuleServer_initializeBehaviorStack(self, experiments, repo, stack, baseGameVersion, includeEditorPacks);
	// }

	// Amethyst::InlineHook<decltype(&RepositorySources::initializePackSource)> _ResourcePackRepository_initializePackSource;
	// void ResourcePackRepository_initializePackSource(ResourcePackRepository* self) {
	// 	_ResourcePackRepository_initializePackSource(self);

	// 	auto& context = Amethyst::GetContext();
	// 	auto& packManager = *context.mPackManager;
	// 	const auto& allPacks = packManager.GetPacks();
	// 	size_t totalSize = std::accumulate(
	// 		allPacks.begin(), allPacks.end(), 0ull,
	// 		[](size_t sum, const auto& pair) {
	// 		return sum + pair.second.size();
	// 	}
	// 	);

	// 	Log::Info("Initializing {} modded pack sources...", totalSize);

	// 	// Add mod "resource_packs" and "behavior_packs" to the CompositePackSource
	// 	for (auto& [nameVer, packs] : allPacks) {
	// 		auto& platform = Amethyst::GetPlatform();
	// 		fs::path modBasePath = platform.GetAmethystFolder() / "mods" / nameVer;

	// 		// Check if the mod has resource packs
	// 		bool hasResourcePacks = std::find_if(packs.begin(), packs.end(), [&](const auto& pair) {
	// 			return pair.second.type == PackType::Resources;
	// 		}) != packs.end();

	// 		// Check if the mod has behavior packs
	// 		bool hasBehaviorPacks = std::find_if(packs.begin(), packs.end(), [&](const auto& pair) {
	// 			return pair.second.type == PackType::Behavior;
	// 		}) != packs.end();

	// 		// Add the resource pack source if it has resource packs
	// 		if (hasResourcePacks) {
	// 			auto& packSource = self->mPackSourceFactory.createDirectoryPackSource(Core::Path((modBasePath / "resource_packs").string()), PackType::Resources, PackOrigin::User, false);
	// 			// self->mPackSource->mPackSources.push_back(&packSource);
	// 		}

	// 		// Add the behavior pack source if it has behavior packs
	// 		if (hasBehaviorPacks) {
	// 			auto& packSource = self->mPackSourceFactory.createDirectoryPackSource(Core::Path((modBasePath / "behavior_packs").string()), PackType::Behavior, PackOrigin::User, false);
	// 			// self->mPackSource->mPackSources.push_back(&packSource);
	// 		}
	// 	}
	// }

	void Initialize() {
		auto& hooks = Amethyst::GetHookManager();
		// VHOOK(VanillaGameModuleServer, initializeBehaviorStack, this);
		// HOOK(ResourcePackRepository, _initializePackSource);
	}
}
#endif