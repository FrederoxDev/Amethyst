#pragma once
#include <minecraft/src-client/common/client/game/ClientInstance.h>
#include <minecraft/src-client/common/client/gui/ScreenView.h>

typedef void (*ModInitialize)(const char* gameVersion);
typedef void (*ModTick)();
typedef void (*ModStartJoinGame)(ClientInstance* clientInstance);
typedef void (*ModShutdown)();
typedef void (*ModRender)(ScreenView* screenView, UIRenderContext* ctx);