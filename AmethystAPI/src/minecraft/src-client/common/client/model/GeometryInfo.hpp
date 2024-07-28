#pragma once
#include <minecraft/src-deps/core/string/StringHash.hpp>

class Geometry;

class GeometryInfo {
public:
    HashedString mName;
    std::unique_ptr<Geometry> mPtr;
};