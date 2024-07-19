#include <amethyst/runtime/ModContext.hpp>
#include <amethyst/MinecraftVtables.hpp>

static AmethystContext* _AmethystContextInstance;

void Amethyst::InitializeAmethystMod(AmethystContext& context)
{
    // Initialize vtbl pointers & ctor pointers.
    InitializeVtablePtrs();

    // Store a persistent AmethystContext instance
    _AmethystContextInstance = &context;
}

Amethyst::EventBus& Amethyst::GetEventBus()
{
    return *_AmethystContextInstance->mEventBus.get();
}

Amethyst::HookManager& Amethyst::GetHookManager()
{
    return *_AmethystContextInstance->mHookManager.get();
}