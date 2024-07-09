#pragma once

enum ChunkState : char {
    Unloaded = 0x0000,
    Generating = 0x0001,
    Generated = 0x0002,
    PostProcessing = 0x0003,
    PostProcessed = 0x0004,
    CheckingForReplacementData = 0x0005,
    NeedsLighting = 0x0006,
    Lighting = 0x0007,
    LightingFinished = 0x0008,
    Loaded = 0x0009,
    Invalid = -1
};
