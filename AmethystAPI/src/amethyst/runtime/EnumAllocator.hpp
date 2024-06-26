#pragma once
#include <minecraft/src-deps/core/string/StringHash.hpp>
#include <cstdint>
#include <map>

struct AllocatedEnum {
    uint64_t mCurrentMaxValue;
};

class EnumAllocator {
public:
    template <typename E>
    void RegisterEnum(E maxExisting) {
        HashType64 enumHash = HashedString::computeHash(typeid(E).name());
        auto it = mEnumsToCurrent.find(enumHash);

        // Only register it on the first call.
        if (mEnumsToCurrent.find(enumHash) != mEnumsToCurrent.end()) return;

        mEnumsToCurrent[enumHash] = AllocatedEnum
        {
            static_cast<uint64_t>(maxExisting)
        };
    }

    template <typename E>
    [[nodiscard]] E GetNextValue() {
        HashType64 enumHash = HashedString::computeHash(typeid(E).name());
        auto it = mEnumsToCurrent.find(enumHash);

        // The enum has not yet been created
        if (it == mEnumsToCurrent.end()) {
            Assert("Tried to allocate a value for '{}', however the enum has not been registered yet.", typeid(E).name());
        }

        // Check the underlying storage type and see if there is still room.
        uint64_t mUnderlyingLimit = std::numeric_limits<E>::max();

        // Well... fuck
        if (it->second.mCurrentMaxValue == mUnderlyingLimit) {
            Assert("Tried to allocate another value for enum '{}', however the maximum limit for the underlying type", typeid(E).name());
        }

        // Increase and return back
        return static_cast<E>(++it->second.mCurrentMaxValue);
    }

private:
    std::map<HashType64, AllocatedEnum> mEnumsToCurrent;
};