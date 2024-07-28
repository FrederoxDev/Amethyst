#pragma once
#include <amethyst/runtime/AmethystContext.hpp>

class RuntimeContext : public AmethystContext {
public:
    RuntimeContext();

    /*
    * @brief Initializes all of the event systems ready for usage in mods
    */
    virtual void Start() override;

    /*
    * @brief Destroys all of the non-persistent data across mod reloads
    */
    virtual void Shutdown() override;
};