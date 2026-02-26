#pragma once
#include <vector>
#include <cstdint>
#include "mc/src-client/common/client/input/Keymapping.hpp"

class RemappingLayout {
public:
    std::vector<Keymapping> mKeymappings;
    std::vector<Keymapping> mDefaultMappings;

    const Keymapping* getKeymappingByAction(const std::string& actionName) const;
    Keymapping* getKeymappingByAction(const std::string& actionName);

    virtual ~RemappingLayout();
    virtual void unknown_1();
    virtual int getAdjustedKey(int);
    virtual void unknown_3();
    virtual std::string getMappedKeyName(int key);
    virtual void unknown_5();
    virtual std::string getMappedKeyName(Keymapping& mapping);

    void assignDefaultMapping(std::vector<Keymapping>&& mapping);
};