#pragma once
#include <minecraft/src/common/world/level/dimension/IDimensionFactory.hpp>
#include <minecraft/src-deps/core/utility/NonOwnerPointer.hpp>
#include <minecraft/src-deps/core/headerIncludes/gsl_includes.hpp>
#include <minecraft/src/common/util/Factory.hpp>
#include <minecraft/src/common/world/level/ILevel.hpp>

namespace br {
namespace worldgen {
struct StructureSetRegistry;
}
} 

class ILevel;
class Scheduler;

class DimensionFactory : public IDimensionFactory {
public:
    gsl::not_null<Bedrock::NonOwnerPointer<ILevel>> mLevel;
    gsl::not_null<Bedrock::NonOwnerPointer<Scheduler>> mScheduler;
    OwnerPtrFactory<Dimension, ILevel&, Scheduler&> mDimensionFactory;
    const br::worldgen::StructureSetRegistry& mStructureSetRegistry;
};