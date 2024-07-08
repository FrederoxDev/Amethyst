#pragma once
#include <shared_mutex>
#include <unordered_map>

class ChunkPos;


class FeatureTerrainAdjustments {
public:
    struct Descriptions;

    std::unordered_map<ChunkPos, FeatureTerrainAdjustments::Descriptions> mDescriptionsToProcess;
    std::shared_mutex mMutex;
};