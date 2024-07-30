#pragma once
#include <string>
#include <minecraft/src-deps/core/string/StringHash.hpp>

struct ActorDefinitionIdentifier {
    std::string mNamespace;
    std::string mIdentifier;
    std::string mInitEvent;
    std::string mFullName;
    HashedString mCanonicalName;
};