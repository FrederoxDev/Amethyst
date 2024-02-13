#pragma once
#include <cstdint>
#include <string>

class SemVersion {
public:
    uint16_t mMajor;
    uint16_t mMinor;
    uint16_t mPatch;
    std::string mPreRelease;
    std::string mBuildMeta;
    std::string mFullVersionString;
    bool mValidVersion;
    bool mAnyVersion;
};