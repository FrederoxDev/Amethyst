#pragma once
#include <amethyst/runtime/events/EventBus.hpp>

class ScreenView;
class MinecraftUIRenderContext;

class BeforeRenderUIEvent : public BaseEvent {
public:
    ScreenView& screen;
    MinecraftUIRenderContext& ctx;

    BeforeRenderUIEvent(ScreenView& screen, MinecraftUIRenderContext& ctx) 
        : screen(screen), ctx(ctx) {}
};

class AfterRenderUIEvent : public BaseEvent {
public:
    ScreenView& screen;
    MinecraftUIRenderContext& ctx;

    AfterRenderUIEvent(ScreenView& screen, MinecraftUIRenderContext& ctx)
        : screen(screen), ctx(ctx) {}
};