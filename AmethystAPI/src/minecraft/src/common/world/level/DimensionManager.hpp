#pragma once
#include <cstdint>
#include <unordered_map>
#include <minecraft/src-deps/core/utility/AutomaticID.hpp>
#include <minecraft/src/common/gamerefs/OwnerPtr.hpp>
#include <minecraft/src/common/gamerefs/WeakRef.hpp>

class Dimension;
class IDimensionFactory;

class DimensionManager {
public:
    std::unordered_map<DimensionType, OwnerPtr<Dimension>> mDimensions;
    const WeakRef<IDimensionFactory> mDimensionFactory;

public:
    // 1.21.0.3 - 48 89 5C 24 ? 44 89 44 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 48 8B FA 4C 8B F9
    WeakRef<Dimension> getOrCreateDimension(DimensionType dimType, int a2);
};