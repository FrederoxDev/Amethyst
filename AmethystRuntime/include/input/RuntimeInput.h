#pragma once
#include <amethyst/InputManager.h>
#include <amethyst/Log.h>
#include <functional>

struct InputAction {
    const std::string mActionName;
    int mDefaultKey = 0;
    bool mAllowRemapping = 0;
    std::function<void(FocusImpact, IClientInstance&)> mButtonDownHandler = NULL;
    std::function<void(FocusImpact, IClientInstance&)> mButtonUpHandler = NULL;
};

class RuntimeInputManager : public InputManager {
public:
    std::vector<InputAction> mInputActions;

public:
    virtual void RegisterInput(const std::string& actionName, int defaultButton, bool allowRemapping = true) override;
    virtual void AddButtonDownHandler(const std::string& actionName, std::function<void(FocusImpact, IClientInstance&)> handler) override;
    virtual void AddButtonUpHandler(const std::string& actionName, std::function<void(FocusImpact, IClientInstance&)> handler) override;
    void Shutdown();
};