#pragma once
#include <string>

class SavedData {
private:
    bool mDirty;
    std::string mId;

public:
    SavedData(const std::string& id) 
        : mId(id), mDirty(false) {};

    virtual ~SavedData() = default;
    virtual void deserialize(const CompoundTag&) = 0;
    virtual void serialize(CompoundTag&) const = 0;

    void setDirty(bool v) {
        mDirty = v;
    }

    bool isDirty() {
        return mDirty;
    }

    const std::string& getId() const {
        return mId;
    }
};