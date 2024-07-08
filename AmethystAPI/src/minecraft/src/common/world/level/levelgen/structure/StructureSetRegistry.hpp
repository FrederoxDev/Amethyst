#pragma once
#include <memory>
#include <string>
#include "entt/container/dense_map.hpp"

namespace br::worldgen {
    class StructureSet;
    
    struct StructureSetRegistry {
        entt::dense_map<std::string, std::shared_ptr<br::worldgen::StructureSet>> mStructureSets;
    };
}