#pragma once
#include "common/client/input/InputHandler.h"

class ClientInstance;
using IClientInstance = ClientInstance;

class ClientInputHandler {
public:
    ClientInstance* mClient;
    bool padding[8];
    InputHandler* mInputHandler;
};