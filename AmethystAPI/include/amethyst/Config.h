#pragma once
#include <vector>
#include <string>
#include "amethyst/Log.h"
#include "Json.hpp"
using json = nlohmann::json;

class Config {
public:
    std::string injectedMod;
    std::vector<std::string> mods; 
    bool promptDebugger;

public:
    Config(std::string& text);
};