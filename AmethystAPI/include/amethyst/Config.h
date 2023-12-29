#pragma once
#include "Json.hpp"
#include "amethyst/Log.h"
#include <string>
#include <vector>
using json = nlohmann::json;

class Config {
public:
    std::string injectedMod;
    std::string version;
    std::vector<std::string> mods; 
    bool promptDebugger;

public:
    Config();
    Config(std::string& text);
};