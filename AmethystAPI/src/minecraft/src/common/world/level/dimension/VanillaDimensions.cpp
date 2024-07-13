#include <minecraft/src/common/world/level/dimension/VanillaDimensions.hpp>
#include <amethyst/Memory.hpp>

const DimensionType VanillaDimensions::Overworld = DimensionType(0);
const DimensionType VanillaDimensions::Nether = DimensionType(1);
const DimensionType VanillaDimensions::TheEnd = DimensionType(2);
const DimensionType VanillaDimensions::Undefined = DimensionType(3);
BidirectionalUnorderedMap<std::string, DimensionType>* VanillaDimensions::DimensionMap = (BidirectionalUnorderedMap<std::string, DimensionType>*)SlideAddress(0x59DE8F0);