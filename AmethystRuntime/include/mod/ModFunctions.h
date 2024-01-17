#pragma once
#include <amethyst/InputManager.h>
#include <common/client/game/ClientInstance.h>
#include <common/client/gui/screens/ScreenView.h>

typedef void (*ModRegisterInputs)(InputManager* inputManager);
typedef void (*ModInitialize)(const char* gameVersion, InputManager* inputManager);
typedef void (*ModStartJoinGame)(ClientInstance* clientInstance);
typedef void (*ModShutdown)();
typedef void (*ModRender)(ScreenView* screenView, UIRenderContext* ctx);
typedef bool (*ModTickBefore)();
typedef void (*ModTickAfter)();