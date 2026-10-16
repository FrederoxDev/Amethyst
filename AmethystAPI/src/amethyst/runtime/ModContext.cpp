#include <amethyst/runtime/ModContext.hpp>
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
    Amethyst::ClientContext* clientCtx = _AmethystContextInstance->mClientCtx.get();

    if (clientCtx == nullptr) {
        AssertFail("Amethyst::GetClientCtx was nullptr!");
    }

    return *clientCtx;
}

Amethyst::ServerContext& Amethyst::GetServerCtx()
{
    Amethyst::ServerContext* serverCtx = _AmethystContextInstance->mServerCtx.get();

    if (serverCtx == nullptr) {
        AssertFail("Amethyst::GetServerCtx was nullptr!");
    }

    return *serverCtx;
}

Amethyst::SharedContext* Amethyst::TryGetCurrentThreadCtx()
{
    switch (Amethyst::GetCurrentThreadClass()) {
    case ThreadClass::MainClient:
        return _AmethystContextInstance->mClientCtx.get();
    case ThreadClass::MainServer:
        return _AmethystContextInstance->mServerCtx.get();
    default:
        return nullptr;
    }
}

Amethyst::SharedContext& Amethyst::GetCurrentThreadCtx()
{
    Amethyst::SharedContext* ctx = Amethyst::TryGetCurrentThreadCtx();

    if (ctx == nullptr) {
        AssertFail("Current thread is {} '{}', not the main Client or Server thread, cannot get context!",
            Amethyst::ToString(Amethyst::GetCurrentThreadClass()), Amethyst::GetCurrentThreadName());
    }

    return *ctx;
}

Amethyst::ThreadClass Amethyst::GetCurrentThreadClass()
{
    if (_AmethystContextInstance == nullptr) {
        return ThreadClass::Unknown;
    }

    return _AmethystContextInstance->mThreadRegistry.GetClass(std::this_thread::get_id());
}

std::string Amethyst::GetCurrentThreadName()
{
    if (_AmethystContextInstance == nullptr) {
        return {};
    }

    return _AmethystContextInstance->mThreadRegistry.Get(std::this_thread::get_id()).mName;
}

bool Amethyst::IsOnAmethystThread()
{
    return Amethyst::GetCurrentThreadClass() == ThreadClass::AmethystRuntime;
}

bool Amethyst::IsOnMainClientThread()
{
    return Amethyst::GetCurrentThreadClass() == ThreadClass::MainClient;
}

bool Amethyst::IsOnMainServerThread()
{
    return Amethyst::GetCurrentThreadClass() == ThreadClass::MainServer;
}

const Amethyst::Mod* Amethyst::GetOwnMod()
{
    return _OwnMod;
}

bool Amethyst::IsAmethystContextInitialized()
{
    return _AmethystContextInstance != nullptr;
}
