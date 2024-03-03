#pragma once
#include <memory>

// class MinecraftGame : public BedrockEngine::AppIsland, App, IMinecraftGame, LevelListener,
//                             ResourcePackListener, OptionsObserver, ActiveDirectoryIdentityObserver

class MinecraftInputHandler;

class MinecraftGame {
public:
    /* this + 0    */ uintptr_t** vtable;
    /* this + 8    */ std::byte padding8[3320];
    /* this + 3328 */ std::unique_ptr<MinecraftInputHandler> mInput;
};