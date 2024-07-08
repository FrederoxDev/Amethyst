#pragma once 
#include <minecraft/src-deps/core/math/DividedPos2d.h>
#include <optional>

class IPreliminarySurfaceProvider {
public:
    virtual ~IPreliminarySurfaceProvider();
    virtual std::optional<short> getPreliminarySurfaceLevel(class DividedPos2d<4>) const = 0;

};