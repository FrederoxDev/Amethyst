#include "minecraft/src-client/common/client/renderer/Tessellator.h"

void Tessellator::begin(const mce::PrimitiveMode mode, const int maxVertices) {
    using function = void(__thiscall*)(Tessellator*, const mce::PrimitiveMode, const int);

    if (this->mTessellating) {
        throw std::exception("Already tessellating!");
    }

    static auto func = reinterpret_cast<function>(SigScan("48 89 5C 24 ? 56 48 83 EC ? 80 B9"));
    func(this, mode, maxVertices);
}

void Tessellator::vertex(float x, float y, float z) {
    using function = void(__thiscall*)(Tessellator*, float, float, float);
    static auto func = reinterpret_cast<function>(SigScan("40 57 48 81 EC ? ? ? ? 0F 29 7C 24 ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 8B 81"));
    func(this, x, y, z);
}

mce::Mesh* Tessellator::end(mce::Mesh* ret, uint64_t a3, std::string_view debugName, int a5) {
    using function = mce::Mesh*(__thiscall*)(Tessellator*, mce::Mesh*, uint64_t, std::string_view, int);
    static auto func = reinterpret_cast<function>(SigScan("48 8B C4 48 89 58 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 70 ? 0F 29 78 ? 44 0F 29 40 ? 44 0F 29 48 ? 44 0F 29 90 ? ? ? ? 44 0F 29 98 ? ? ? ? 44 0F 29 A0 ? ? ? ? 44 0F 29 A8 ? ? ? ? 44 0F 29 B0 ? ? ? ? 44 0F 29 B8 ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4D 8B F9"));
    return func(this, ret, a3, debugName, a5);
}
