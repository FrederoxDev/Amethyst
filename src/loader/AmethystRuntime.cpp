#include "loader/AmethystRuntime.hpp"

#include "amethyst/Log.hpp"
#include "amethyst/runtime/ModContext.hpp"
#include "amethyst/runtime/events/ModEvents.hpp"
#include "amethyst/runtime/events/InputEvents.hpp"
#include "debug/AmethystDebugging.hpp"
#include "loader/RuntimeContext.hpp"

#include <unordered_set>
#include <vector>

AmethystRuntime* AmethystRuntime::instance = nullptr;
extern HMODULE hModule;
extern HANDLE gMcThreadHandle;
extern DWORD gMcThreadId;

AmethystRuntime::AmethystRuntime(std::unique_ptr<Amethyst::Platform> platform)
    : mAmethystContext(std::move(platform))
{
    AmethystRuntime::instance = this;
}

void AmethystRuntime::Start()
{
    Assert(!mRunning, "AmethystRuntime::Start called whilst running!");
    auto& platform = Amethyst::GetPlatform();

    // The launcher decided what this launch is, everything below is driven by it
    mSession = Amethyst::SessionManifest::FindForCurrentProcess();
    Assert(mSession.runtime.has_value(), "Profile '{}' has no runtime, yet the runtime was injected", mSession.profileName);

    // Prompt a debugger if they are in developer mode
    if (mSession.developerMode)
        platform.AttachDebugger();

    Amethyst::GetContext().Start();

    // Load all mod DLLs and call their initialize functions
    LoadModDlls();
    mRunning = true;
}

void AmethystRuntime::LoadModDlls()
{
    Amethyst::ModRepository& repository = *mAmethystContext.mModRepository;
    Amethyst::ModGraph& modGraph = *mAmethystContext.mModGraph;
    Amethyst::ModLoader& modLoader = *mAmethystContext.mModLoader;

    // Register mod inputs
    // On game start mOptions will be nullptr, but the register inputs event gets called when options is created.
    // When hot-reloading we will have options already so we can register inputs here.
	#ifdef CLIENT
    if (Amethyst::GetClientCtx().mOptions != nullptr) {
        // RegisterInputsEvent event(*Amethyst::GetContext().mInputManager.get());
        // Amethyst::GetEventBus().Invoke(event);
    }
	#endif

    // The session names every mod of the profile, the runtime itself included
    std::vector<fs::path> directories;
    std::unordered_set<std::string> ids;

    for (const auto& mod : mSession.mods) {
        directories.push_back(mod.directory);
        ids.insert(mod.id);
    }

    repository.LoadFromDirectories(directories);
    for (const auto& error : repository.GetErrors()) {
        Log::Error("{}", error.toString());
    }

    modGraph.SortAndValidate(repository, ids);

    for (const auto& modInfo : modGraph.GetMods()) {
        if (modInfo->UUID == "00000000-0000-0000-0000-000000000000") {
            Log::Warning("Mod '{}' has the default UUID of '00000000-0000-0000-0000-000000000000' in its mod.json! It is recommended to generate a new one", modInfo->GetVersionedName());
        }
    }

    for (const auto& error : modGraph.GetErrors()) {
        Log::Error("{}", error.toString());
    }

    modLoader.LoadGraph(modGraph);
    for (const auto& error : modLoader.GetErrors()) {
        Log::Error("{}", error.toString());
    }

    // Allow mods to add listeners to eachothers events
    AddModEventListenersEvent event;
    Amethyst::GetEventBus().Invoke<AddModEventListenersEvent>(event);
}

void AmethystRuntime::WatchForHotReload()
{
    auto& platform = Amethyst::GetPlatform();

    // Runs on Amethyst's own thread, so this is the one place its id can be taken without
    // having to be told which thread it is.
    mAmethystContext.mThreadRegistry.Record(
        std::this_thread::get_id(), Amethyst::ThreadClass::AmethystRuntime, {});

    // No resume to balance here any more. Startup never suspends the game: the runtime is
    // loaded before the game's entry point, so there is nothing running to hold still. The
    // pause below is the only one left, and it happens with the game up and this loop on a
    // thread of its own, which is where suspending it is safe.
    while (true) {
        Sleep(1000 / 20);

        if (platform.HasRequestedStop()) break;

        if (platform.HasRequestedHotReload() && mRunning == true) {
            Log::Info("\n========================= Starting hot-reload! =========================");

            platform.PauseGameThread();
            Shutdown();
            Start();
            platform.ResumeGameThread();
        }
    }
}

void AmethystRuntime::Shutdown()
{
    if (!mRunning)
        return;

    BeforeModShutdownEvent shutdownEvent;
    Amethyst::GetEventBus().ReverseInvoke(shutdownEvent);

    // Clear lists of mods & functions.
    Amethyst::GetContext().Shutdown();
    mRunning = false;
}

extern "C" __declspec(dllexport) 
AmethystContext* GetContextInstance()
{
    return &Amethyst::GetContext();
}
