#include "mod/AmethystMod.hpp"
#include "amethyst/runtime/ModContext.hpp"
#include "amethyst/runtime/events/ModEvents.hpp"
#include "hooks/client/Client.hpp"
#include "hooks/shared/Shared.hpp"

extern const Amethyst::Mod* _OwnMod;

ModFunction void Initialize(AmethystContext& ctx, const Amethyst::Mod& mod)
{
    Amethyst::InitializeAmethystMod(ctx, mod);
    Amethyst::EventBus& events = *ctx.mEventBus;
    events.AddListener<BeforeModShutdownEvent>([&](const BeforeModShutdownEvent& e) {
        _OwnMod = nullptr;
    });

#ifdef CLIENT
	Amethyst::ClientHooks::Initialize();

#endif
	Amethyst::SharedHooks::Initialize();
}