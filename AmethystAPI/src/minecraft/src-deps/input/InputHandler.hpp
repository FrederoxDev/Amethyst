#pragma once
#include "amethyst/Memory.hpp"
#include <functional>
#include <string>
#include <map>

enum FocusImpact : char {
    Neutral = 0x0,
    ActivateFocus = 0x1,
    DeactivateFocus = 0x2,
};

class ClientInstance;
using IClientInstance = ClientInstance;

int StringToNameId(const std::string& str);

class InputHandler {
public:
    /* this + 0   */ std::byte padding0[24];
    /* this + 24  */ std::multimap<unsigned int, std::pair<bool, std::function<void(enum FocusImpact, IClientInstance &)>>> mButtonDownHandlerMap;
    /* this + 40  */ std::multimap<unsigned int, std::pair<bool, std::function<void(enum FocusImpact, IClientInstance&)>>> mButtonUpHandlerMap;

public:
    void registerButtonDownHandler(std::string buttonName, std::function<void(FocusImpact, IClientInstance&)> handler, bool suspendable);
    void registerButtonUpHandler(std::string buttonName, std::function<void(FocusImpact, IClientInstance&)> handler, bool suspendable);
};