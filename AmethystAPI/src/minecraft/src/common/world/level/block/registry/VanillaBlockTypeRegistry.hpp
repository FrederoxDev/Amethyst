#pragma once

class Experiments;
class BaseGameVersion;

namespace VanillaBlockTypes {
    // 1.20.51.1 - 48 89 54 24 ? 48 89 4C 24 ? 56 57 B8
    void registerBlocks(const BaseGameVersion& baseGameVersion, const Experiments& experiments);
};