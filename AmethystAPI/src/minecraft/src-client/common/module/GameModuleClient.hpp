#pragma once
#include <cstdint>

class GameModuleClient {
public:
    enum ResourceLoadingPhase : int32_t {
        AppStartup,
        Frontend,
        InGame
    };
};