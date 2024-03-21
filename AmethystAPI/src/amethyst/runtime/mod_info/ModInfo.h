#pragma once
#include "Json.hpp"
#include "amethyst/Log.h"
#include <optional>
#include <string>
using json = nlohmann::json;

namespace Amethyst {
    class ModInfo {

    public:
        struct Meta {
            std::string name;
            std::string version;
            std::string author;
        };

    public:
        static std::optional<ModInfo> getModInfoFromText(std::string modName, std::string text);
        Meta meta;
    };
}