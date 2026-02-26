#include "mc/src-client/common/client/gui/gui/UIControl.hpp"
#include <amethyst/Memory.hpp>
#include <mc/src-client/common/client/gui/controls/CustomRenderComponent.hpp>

std::string UIControl::getPathedName()
{
    if (!mParent.expired()) {
        auto sharedParent = mParent.lock();

        if (sharedParent) {
            return sharedParent->getPathedName() + "\\" + mName;
        }
    }

    return mName;
}

template <>
void UIControl::setComponent<CustomRenderComponent>(std::unique_ptr<CustomRenderComponent> component)
{
    using function = decltype(&UIControl::setComponent<CustomRenderComponent>); 
    static function func = std::bit_cast<function>(SigScan("48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 83 EC ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 4C 8B E2 4C 8B E9 48 89 54 24 ? E8 ? ? ? ? 4C 8B 48 ? 4C 89 4C 24 ? 49 8D 41 ? 4D 8B 85 ? ? ? ? 49 8B D0 48 23 D0 48 8B C2 48 D1 E8 48 B9 ? ? ? ? ? ? ? ? 48 23 C1 48 2B D0 48 8B CA 48 C1 E9 ? 48 B8 ? ? ? ? ? ? ? ? 48 23 C8 48 23 D0 48 03 CA 49 8B 2C 24 48 89 6C 24 ? 4D 8D BD ? ? ? ? 48 8B C1 48 C1 E8 ? 48 03 C1 48 B9 ? ? ? ? ? ? ? ? 48 23 C1 48 B9 ? ? ? ? ? ? ? ? 48 0F AF C1 48 C1 E8 ? 48 8D 3C C5 ? ? ? ? 4D 85 C1 0F 85 ? ? ? ? 33 DB 49 89 1C 24 48 89 6C 24 ? 4D 8B 37 4C 03 F7 49 8B 77 ? 49 3B 77 ? 0F 84 ? ? ? ? 4C 3B F6 75 ? 48 89 2E 49 83 47 ? ? E9 ? ? ? ? 48 8D 7E ? 48 8B 07 48 89 1F 48 89 06 49 83 47 ? ? 49 3B FE 74 ? 90 48 83 EF ? 48 83 EE ? 48 3B F7 74 ? 48 8B 07 48 89 1F 48 8B 0E 48 89 06 48 85 C9 74 ? 48 8B 01 BA ? ? ? ? 48 8B 00 FF 15 ? ? ? ? 49 3B FE 75 ? 48 8D 44 24 ? 4C 3B F0 74 ? 48 8B C5 48 8B EB 49 8B 0E 49 89 06 48 85 C9 74 ? 48 8B 01 BA ? ? ? ? 48 8B 00 FF 15 ? ? ? ? 48 85 ED 74 ? 48 8B 45 ? BA ? ? ? ? 48 8B CD 48 8B 00 FF 15 ? ? ? ? 48 8B 6C 24 ? 48 85 DB 74 ? 48 8B 03 BA ? ? ? ? 48 8B CB 48 8B 00 FF 15 ? ? ? ? 48 8B 44 24 ? 49 09 85 ? ? ? ? EB ? 4C 8D 44 24 ? 49 8B D6 49 8B CF E8 ? ? ? ? 48 8B 5C 24 ? EB ? 49 8B 07 48 8B 14 07 49 8B CD E8 ? ? ? ? 49 8B 0F 49 8B 04 24 33 DB 49 89 1C 24 4C 8B 04 39 48 89 04 39 4D 85 C0 74 ? 49 8B 00 8D 53 ? 49 8B C8 48 8B 00 FF 15 ? ? ? ? 48 8B D5 49 8B CD E8 ? ? ? ? 90 49 8B 0C 24 48 85 C9 74 ? 48 8B 01 BA ? ? ? ? 48 8B 00 FF 15 ? ? ? ? 48 8B 4C 24 ? 48 33 CC E8 ? ? ? ? 48 8B 9C 24 ? ? ? ? 48 83 C4 ? 41 5F 41 5E 41 5D 41 5C 5F 5E 5D C3 CC CC CC CC CC CC CC CC CC CC CC CC CC 48 89 5C 24 ? 57"));
    (this->*func)(std::move(component));
}

template <>
CustomRenderComponent* UIControl::getComponent<CustomRenderComponent>()
{
    using function = decltype(&UIControl::getComponent<CustomRenderComponent>);
    static function func = std::bit_cast<function>(SigScan("40 53 48 83 EC ? 48 8B D9 E8 ? ? ? ? 48 8B 50 ? 48 8B 83 ? ? ? ? 48 85 C2 0F 84 ? ? ? ? 48 FF CA 48 B9 ? ? ? ? ? ? ? ? 48 23 D0 48 8B C2 48 D1 E8 48 23 C1 48 B9 ? ? ? ? ? ? ? ? 48 2B D0 48 8B C2 48 23 D1 48 C1 E8 ? 48 23 C1 48 8B 8B ? ? ? ? 48 03 C2 48 8B D0 48 C1 EA ? 48 03 D0 48 B8 ? ? ? ? ? ? ? ? 48 23 D0 48 B8 ? ? ? ? ? ? ? ? 48 0F AF D0 48 8B 83 ? ? ? ? 48 2B C8 48 C1 EA ? 48 C1 F9 ? 48 3B D1 73 ? 48 8B 04 D0 48 83 C4 ? 5B C3 33 C0 48 83 C4 ? 5B C3 CC CC CC 48 89 5C 24 ? 48 89 74 24 ? 57 B8"));
    return (this->*func)();
}