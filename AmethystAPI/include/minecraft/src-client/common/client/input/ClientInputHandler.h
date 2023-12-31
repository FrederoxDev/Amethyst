#pragma once
#include "minecraft/src-deps/input/InputHandler.h"

class ClientInstance;
using IClientInstance = ClientInstance;

class ClientInputHandler {
    ClientInstance* mClient;
    InputHandler* mInputHandler;
};