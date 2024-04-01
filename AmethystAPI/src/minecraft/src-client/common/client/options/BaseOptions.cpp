#include "minecraft/src-client/common/client/options/BaseOptions.hpp"

float BaseOptions::getSensitivity(unsigned int inputMode) {
    using function = decltype(&BaseOptions::getSensitivity);
    static auto func = std::bit_cast<function>(SigScan("40 53 48 83 EC ? 80 B9 ? ? ? ? ? 8B DA"));
    return (this->*func)(inputMode);
}