#pragma once
#include <functional>
#include <gsl/gsl_util>

class ItemStackNetManagerBase {
public:
    virtual ~ItemStackNetManagerBase() = default;
    virtual void unk1();
    virtual void unk2();
    virtual void unk3();
    virtual void unk4();
    virtual gsl::final_action<std::function<void(void)>> _tryBeginClientLegacyTransactionRequest();
};