#ifdef CLIENT
#include <amethyst/runtime/ModContext.hpp>
#include <amethyst/runtime/utility/InlineHook.hpp>
#include <amethyst/Log.hpp>

#include <module/VanillaGameModuleClient.hpp>
#include <resources/RepositorySources.hpp>
#include <resources/PackSourceFactory.hpp>
#include <resources/PackSource.hpp>
#include <Core/Resource/PackType.hpp>
#include <Core/File/Path.hpp>
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
		context.mPackManager->AddResourcePacksToStack(repo, stack);
		_VanillaGameModuleClient_initializeResourceStack(self, experiments, repo, stack, baseGameVersion, loadingPhase, includeEditorPacks);
	}

	Amethyst::InlineHook<decltype(&RepositorySources::initializePackSource)> _RepositorySources_initializePackSource;
	void RepositorySources_initializePackSource(RepositorySources* self, PackSourceFactory& factory)
	{
		_RepositorySources_initializePackSource(self, factory);

		auto& platform = Amethyst::GetPlatform();
		auto& packManager = *Amethyst::GetContext().mPackManager;
		for (const auto& [modKey, packs] : packManager.GetPacks()) {
			std::filesystem::path modBase = platform.GetAmethystFolder() / "Mods" / modKey;
			bool hasRP = false, hasBP = false;
			for (const auto& [_, pack] : packs) {
				if (pack.type == PackType::Resources) hasRP = true;
				else if (pack.type == PackType::Behavior) hasBP = true;
			}
			if (hasRP) {
				auto rpDir = (modBase / "resource_packs").generic_string();
				auto& src = factory.createDirectoryPackSource(::Core::Path(rpDir), PackType::Resources, kPackOriginUser, false);
				self->mPackSource->addPackSource(&src);
				Log::Info("[Amethyst::PackManager] Registered RP source: {}", rpDir);
			}
			if (hasBP) {
				auto bpDir = (modBase / "behavior_packs").generic_string();
				auto& src = factory.createDirectoryPackSource(::Core::Path(bpDir), PackType::Behavior, kPackOriginUser, false);
				self->mPackSource->addPackSource(&src);
				Log::Info("[Amethyst::PackManager] Registered BP source: {}", bpDir);
			}
		}
	}

	void Initialize() {
		auto& hooks = Amethyst::GetHookManager();
		VHOOK(VanillaGameModuleClient, initializeResourceStack, VanillaGameModuleClient::$vtable_for_VanillaGameModuleClient);
		HOOK(RepositorySources, initializePackSource);
	}
}
#endif