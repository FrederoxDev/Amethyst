#include "minecraft/src-client/common/client/gui/gui/UIControl.hpp"
#include <minecraft/src-client/common/client/gui/controls/ToggleComponent.hpp>
#include <minecraft/src-client/common/client/gui/controls/SliderComponent.hpp>
#include <minecraft/src-client/common/client/gui/controls/TextComponent.hpp>
#include <amethyst/Memory.hpp>

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
ToggleComponent* UIControl::getComponent<ToggleComponent>() {
    for (auto& component : mComponents) {
        // 1.20.71.1 - 0x53a2258
        // Vtable for ToggleComponent
        // Found by logging this* in ToggleComponent::setChecked
        if ((uintptr_t)component->vtable != SlideAddress(0x53a2258)) continue;
        return (ToggleComponent*)component.get();
    }

    return nullptr;
}

template <>
SliderComponent* UIControl::getComponent<SliderComponent>() {
    for (auto& component : mComponents) {
        // 1.20.71.1 - 0x539c7a0
        // Vtable for SliderComponent
        // Found by logging this* in SliderComponent::_updateSliderFromStepSize
        if ((uintptr_t)component->vtable != SlideAddress(0x539c7a0)) continue;
        return (SliderComponent*)component.get();
    }

    return nullptr;
}

template <>
TextComponent* UIControl::getComponent<TextComponent>()
{
    for (auto& component : mComponents) {
        // 1.20.71.1 - 0x53a23c8
        // Vtable for TextComponent
        // Found by xrefing TextComponent::updateUI
        if ((uintptr_t)component->vtable != SlideAddress(0x53a23c8)) continue;
        return (TextComponent*)component.get();
    }

    return nullptr;
}