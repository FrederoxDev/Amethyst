#pragma once
#include <chrono>

class ActorTerrainInterlockData {
public:
    enum VisibilityState : unsigned char {
        InitialNotVisible, 
        Visible, 
        DelayedDestructionNotVisible
    };

    ActorTerrainInterlockData::VisibilityState mRenderVisibilityState;
    std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds> mCreationTime;
    bool mHasBeenDelayedDeleted;
};