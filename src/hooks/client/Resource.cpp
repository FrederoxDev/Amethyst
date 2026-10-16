#ifdef CLIENT
#include <amethyst/runtime/ModContext.hpp>
#include <amethyst/runtime/utility/InlineHook.hpp>
#include <amethyst/Log.hpp>

#include <module/VanillaGameModuleClient.hpp>
#include <resources/RepositorySources.hpp>
#include <resources/ResourcePackManager.hpp>
#include <resources/ResourcePackStack.hpp>
#include <resources/PackSourceFactory.hpp>
#include <resources/PackSource.hpp>
#include <client/game/ClientInstance.hpp>
#include <Core/Resource/PackType.hpp>
#include <Core/File/Path.hpp>
#include <algorithm>
#include <filesystem>

static constexpr auto kPackOriginUser = static_cast<PackOrigin>(6);

namespace Amethyst::ClientHooks::ResourceHooks {
	Amethyst::InlineHook<decltype(&VanillaGameModuleClient::initializeResourceStack)> _VanillaGameModuleClient_initializeResourceStack;
	void VanillaGameModuleClient_initializeResourceStack(
		VanillaGameModuleClient* self,
		const Experiments* experiments,
		const ::gsl::not_null<::Bedrock::NonOwnerPointer<IResourcePackRepository>>& repo,
		ResourcePackStack& stack,
		const BaseGameVersion& baseGameVersion,
		::GameModuleClient::ResourceLoadingPhase loadingPhase,
		bool includeEditorPacks
	) {
		auto& context = Amethyst::GetContext();
		context.mPackManager->AddResourcePacksToStack(*repo, stack);
		_VanillaGameModuleClient_initializeResourceStack(self, experiments, repo, stack, baseGameVersion, loadingPhase, includeEditorPacks);
	}

	Amethyst::InlineHook<decltype(&ResourcePackManager::composeFullStack)> _ResourcePackManager_composeFullStack;
	int ResourcePackManager_composeFullStack(
		const ResourcePackManager* self,
		ResourcePackStack& output,
		const ResourcePackStack& globalStack,
		const ResourcePackStack& levelStack
	) {
		int offset = _ResourcePackManager_composeFullStack(self, output, globalStack, levelStack);

		ClientInstance* clientInstance = Amethyst::GetClientCtx().mClientInstance;
		if (clientInstance) {
			IResourcePackRepository& repository = clientInstance->getResourcePackRepository();
			auto& packManager = *Amethyst::GetContext().mPackManager;

			// ResourcePackManager::_loadHelper walks the stack front-to-back and returns the
			// first pack holding the file, so position IS priority. AddResourcePacksToStack
			// appends, which would leave mod packs behind the base game and make any file a
			// mod overrides unreachable. Move them to the front, where vanilla itself puts
			// the addon stack, so a mod can override a vanilla resource and not just add one.
			const size_t before = output.mStack.size();
			packManager.AddResourcePacksToStack(repository, output);
			const size_t added = output.mStack.size() - before;
			if (added > 0) {
				std::rotate(output.mStack.begin(), output.mStack.end() - added, output.mStack.end());
			}
		}
		return offset;
	}

	Amethyst::InlineHook<decltype(&RepositorySources::initializePackSource)> _RepositorySources_initializePackSource;
	void RepositorySources_initializePackSource(RepositorySources* self, PackSourceFactory& factory)
	{
		_RepositorySources_initializePackSource(self, factory);

		auto& packManager = *Amethyst::GetContext().mPackManager;
		for (const auto& [modKey, packs] : packManager.GetPacks()) {
			if (packs.empty()) continue;
			std::filesystem::path modBase = packs.begin()->second.owner->mInfo->Directory;
			bool hasRP = false, hasBP = false;
			for (const auto& [_, pack] : packs) {
				if (pack.type == PackType::Resources) hasRP = true;
				else if (pack.type == PackType::Behavior) hasBP = true;
			}
			if (hasRP) {
				auto rpDir = (modBase / "resource_packs").generic_string();
				auto& src = factory.createDirectoryPackSource(::Core::Path(rpDir), PackType::Resources, kPackOriginUser, false);
				self->mPackSource->addPackSource(&src);
			}
			if (hasBP) {
				auto bpDir = (modBase / "behavior_packs").generic_string();
				auto& src = factory.createDirectoryPackSource(::Core::Path(bpDir), PackType::Behavior, kPackOriginUser, false);
				self->mPackSource->addPackSource(&src);
			}
		}
	}

	void Initialize() {
		auto& hooks = Amethyst::GetHookManager();
		HOOK(VanillaGameModuleClient, initializeResourceStack);
		HOOK(ResourcePackManager, composeFullStack);
		HOOK(RepositorySources, initializePackSource);
	}
}
#endif
