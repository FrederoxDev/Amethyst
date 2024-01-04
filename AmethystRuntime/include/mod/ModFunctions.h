#pragma once
#include <amethyst/InputManager.h>
#include <minecraft/src-client/common/client/game/ClientInstance.h>
#include <minecraft/src-client/common/client/gui/ScreenView.h>

typedef void (*ModRegisterInputs)(InputManager* inputManager);
typedef void (*ModInitialize)(const char* gameVersion, InputManager* inputManager);
typedef void (*ModTick)();
typedef void (*ModStartJoinGame)(ClientInstance* clientInstance);
typedef void (*ModShutdown)();
typedef void (*ModRender)(ScreenView* screenView, UIRenderContext* ctx);