#include "minecraft/src-client/common/client/gui/gui/UIControl.h"
#include <minecraft/src-client/common/client/gui/controls/ToggleComponent.h>
#include <amethyst/Memory.h>

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