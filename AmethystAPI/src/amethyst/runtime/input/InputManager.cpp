#include <utility>

#include "amethyst/runtime/input/InputManager.hpp"
#include "amethyst/runtime/AmethystContext.hpp"

Amethyst::InputManager::InputManager(AmethystContext& ctx)
    : mAmethyst(ctx), mHasCopiedVanillaInputs(false) {}

Amethyst::InputManager::~InputManager()
{
    // Validate we are far enough into the game where inputs have actually been registered.
    if (!mHasCopiedVanillaInputs) return;

    InputHandler* vanillaInputHandler = mAmethyst.mClientInstance->inputHandler->mInputHandler;

    // Restore all the default vanilla button handlers
    vanillaInputHandler->mButtonDownHandlerMap = mVanillaButtonDownHandlerMap;
    vanillaInputHandler->mButtonUpHandlerMap = mVanillaButtonUpHandlerMap;
}

void Amethyst::InputManager::_copyVanillaInputs()
{
    ClientInputHandler* clientInputHandler = mAmethyst.mClientInstance->inputHandler;
    if (mHasCopiedVanillaInputs || clientInputHandler == nullptr) return;

    InputHandler* vanillaInputHandler = clientInputHandler->mInputHandler;

    mVanillaButtonDownHandlerMap = vanillaInputHandler->mButtonDownHandlerMap;
    mVanillaButtonUpHandlerMap = vanillaInputHandler->mButtonUpHandlerMap;

    mHasCopiedVanillaInputs = true;
}
