#include "minecraft/src/common/world/level/block/BlockLegacy.h"

#pragma warning(push)
#pragma warning(disable : 26495)
BlockLegacy::BlockLegacy(const std::string& nameId, int id, const Material& material) {
    using function = BlockLegacy*(__thiscall*)(BlockLegacy*, const std::string&, int, const Material&);

    static auto func = reinterpret_cast<function>(
            SigScan("48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 81 EC ? ? ? ? 49 8B F9 48 8B F2"));

    func(this, nameId, id, material);
}
#pragma warning(pop)

BlockLegacy::~BlockLegacy() {

}