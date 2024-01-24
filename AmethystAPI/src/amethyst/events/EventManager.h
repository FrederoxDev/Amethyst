#pragma once
#include "amethyst/events/Event.h"
#include "minecraft/src-client/common/client/game/ClientInstance.h"
#include "minecraft/src-client/common/client/gui/ScreenView.h"

namespace Amethyst {
class EventManager {
public:
    Event<ClientInstance*> onStartJoinGame;
    Event<ScreenView*, UIRenderContext*> onRenderUI;
    Event<> beforeTick;
    Event<> afterTick;

private:
    std::unordered_map<size_t, uintptr_t> mFuncHashToOriginalAddress;

public:
    template <typename Func>
    void CreateNewEvent(Func function, std::string_view signature)
    {
        uintptr_t address = SigScan(signature);
        CreateNewEvent(function, address);
    }

    template <typename Func>
    void CreateNewEvent(Func function, uintptr_t address)
    {
        // Converts the function to a unique hashed number
        size_t hash = typeid(function).hash_code();

        // Check if the event has already been created, if so ignore
        if (mFuncHashToOriginalAddress.find(hash) != mFuncHashToOriginalAddress.end())
            return;

        // Store the original address of the function
        mFuncHashToOriginalAddress[hash] = address;
    }

    /*
    Clear any events that have been registered
    */
    void Shutdown()
    {
        onStartJoinGame.Shutdown();
        onRenderUI.Shutdown();
        beforeTick.Shutdown();
        afterTick.Shutdown();
    }
};
} // namespace Amethyst