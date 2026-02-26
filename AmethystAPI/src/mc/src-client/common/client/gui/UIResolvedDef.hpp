/// @symbols
#pragma once
#include <amethyst/Imports.hpp>
#include <string>
#include <set>
#include <vector>
#include <json/json.h>

class UIResolvedDef {
public:
    bool mIgnored;
    const std::string mDefNamespace;
    const std::string mDefName;

    // anything below here seems to be completely broken
    const Json::Value& mBaseVal;
    const Json::Value& mOverrideVal;
    Json::Value mVariables;
    std::vector<Json::Value*>* mVariablesStack;
    std::set<std::string> mUnvalidatedProperties;

	/// @address {0x4620280}
    MC std::string getAsString(std::string_view key) const;
};