#pragma once
#include <string>

enum ItemIconInfoType : __int32 {
    Icon = 0x0,
    Atlas = 0x1,
    RawUVs = 0x2,
    LegacyBlock = 0x3,
};

struct ResolvedItemIconInfo {
    std::string mIconName;
    int mIconFrame;
    ItemIconInfoType mIconType;
    unsigned int mRuntimeBlockID;
    float mU0;
    float mV0;
    float mU1;
    float mV1;
    unsigned __int16 mTexSizeW;
    unsigned __int16 mTexSizeH;
};