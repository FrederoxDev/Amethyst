#include "minecraft/src-deps/input/InputHandler.h"

void InputHandler::registerButtonDownHandler(std::string a1, std::function<void(FocusImpact, IClientInstance&)> a2, bool a3) {
	using function = void(__thiscall*)(InputHandler*, std::string, std::function<void(FocusImpact, IClientInstance&)>, bool);
    static auto func = reinterpret_cast<function>(SlideAddress(0x3AFC790));
        return func(this, a1, a2, a3);
}