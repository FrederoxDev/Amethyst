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

Amethyst::RuntimeFeatures& Amethyst::GetFeatures()
{
    return *_AmethystContextInstance->mFeatures.get();
}

Amethyst::InputManager& Amethyst::GetInputManager()
{
    return *_AmethystContextInstance->mInputManager.get();
}
