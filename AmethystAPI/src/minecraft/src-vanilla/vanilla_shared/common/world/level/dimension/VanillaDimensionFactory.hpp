#pragma once
#include <minecraft/src/common/util/Factory.hpp>

class ILevel;
class Scheduler;
class Dimension;

namespace VanillaDimensionFactory {
    // 1.21.0.3 - 0x40818E0 (signature is incredibly long..)
    void registerDimensionTypes(OwnerPtrFactory<Dimension, ILevel&, Scheduler&>& factory);
};