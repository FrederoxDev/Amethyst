#pragma once
#include <amethyst/InputManager.h>
#include <minecraft/src-client/common/client/game/ClientInstance.h>
#include <minecraft/src-client/common/client/gui/ScreenView.h>
#include <amethyst/events/EventManager.h>
#include <amethyst/HookManager.h>

typedef void (*ModRegisterInputs)(InputManager* inputManager);
typedef void (*ModInitialize)(HookManager* hookManager, Amethyst::EventManager* eventManager, InputManager* inputManager);
typedef void (*ModShutdown)();