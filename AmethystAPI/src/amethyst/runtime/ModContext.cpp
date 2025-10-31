#include <amethyst/runtime/ModContext.hpp>
#include <mc/src/common/Minecraft.hpp>
#include <thread>
#include <amethyst/runtime/ctx/SharedContext.hpp>
#include <amethyst/runtime/ctx/ServerContext.hpp>
#include <amethyst/runtime/ctx/ClientContext.hpp>

AmethystContext* _AmethystContextInstance = nullptr;
const Amethyst::Mod* _OwnMod = nullptr;

void Amethyst::InitializeAmethystMod(AmethystContext& context, const Mod& mod)
{
    // Store a persistent AmethystContext instance
    _AmethystContextInstance = &context;

    // Store our own mod info for later retrieval
    _OwnMod = &mod;

    // Do a quick sanity check by comparing some important class sizes and offsets
    if (context.mAmethystAbiHash != AmethystContext::GetAmethystAbiHash()) {
        Log::Warning("Detected difference in amethyst ABI hash! This mod is not compatible with this version of the runtime! Please recompile the mod/runtime if developing!");
    }

    // Check if the mod has a resource pack and register it if it does
    if (fs::exists(mod.mInfo->Directory / "resource_packs" / "main_rp" / "manifest.json"))
        context.mPackManager->RegisterNewPack(&mod, "main_rp", PackType::Resources);

    // Check if the mod has a behavior pack and register it if it does
    if (fs::exists(mod.mInfo->Directory / "behavior_packs" / "main_bp" / "manifest.json"))
        context.mPackManager->RegisterNewPack(&mod, "main_bp", PackType::Behavior);
}

AmethystContext& Amethyst::GetContext()
{
    return *_AmethystContextInstance;
}

Amethyst::EventBus& Amethyst::GetEventBus()
{
    return *_AmethystContextInstance->mEventBus.get();
}

Amethyst::HookManager& Amethyst::GetHookManager()
{
    return *_AmethystContextInstance->mHookManager.get();
}

Amethyst::PatchManager& Amethyst::GetPatchManager()
{
    return *_AmethystContextInstance->mPatchManager.get();
}

Amethyst::EnumAllocator& Amethyst::GetEnumAllocator()
{
    return *_AmethystContextInstance->mEnumAllocator.get();
}

Amethyst::NetworkManager& Amethyst::GetNetworkManager()
{
    return *_AmethystContextInstance->mNetworkManager.get();
}

Amethyst::Platform& Amethyst::GetPlatform()
{
    Amethyst::Platform* platform = _AmethystContextInstance->mPlatform.get();

    if (platform == nullptr) {
        AssertFail("Amethyst::GetPlatform was nullptr!");
    }

    return *platform;
}

Amethyst::ClientContext& Amethyst::GetClientCtx()
{
    return *_AmethystContextInstance->mClientCtx;
}

Amethyst::ServerContext& Amethyst::GetServerCtx()
{
    return *_AmethystContextInstance->mServerCtx;
}

Amethyst::SharedContext& Amethyst::GetCurrentThreadCtx()
{
    if (Amethyst::IsOnMainClientThread()) {
        return *_AmethystContextInstance->mClientCtx;
    } 
    else if (Amethyst::IsOnMainServerThread()) {
        return *_AmethystContextInstance->mServerCtx;
    }

    AssertFail("Current thread is not the main Client or Server thread, cannot get context!");
}

bool Amethyst::IsOnAmethystThread()
{
    return _AmethystContextInstance->mAmethystThread == std::this_thread::get_id();
}

bool Amethyst::IsOnMainClientThread()
{
    return _AmethystContextInstance->mMainClientThread == std::this_thread::get_id();
}

bool Amethyst::IsOnMainServerThread()
{
    return _AmethystContextInstance->mMainServerThread == std::this_thread::get_id();
}

const Amethyst::Mod* Amethyst::GetOwnMod()
{
    return _OwnMod;
}

bool Amethyst::IsAmethystContextInitialized()
{
    return _AmethystContextInstance != nullptr;
}
