#pragma once
#include <minecraft/src-deps/core/string/StringHash.hpp>
#include <cstdint>
#include <map>

#ifdef max
#undef max
#endif

namespace Amethyst {
    /*
    A class which allows mods to safely use customly made enumerators, without having to worry about other mods using the same values.
    */
    class EnumAllocator {
    public:
        /**
         * @brief Used to internally initialize the highest value of an enum.
         * @tparam E - The enum to allocate new values.
         * @param maxExisting - The highest existing value in the enum.
         */
        template <typename E>
        void RegisterEnum(E maxExisting) {
            HashType64 enumHash = HashedString::computeHash(typeid(E).name());
            auto it = mEnumsToCurrent.find(enumHash);

            // Only register it on the first call.
            if (mEnumsToCurrent.find(enumHash) != mEnumsToCurrent.end()) return;

            mEnumsToCurrent[enumHash] = static_cast<uint64_t>(maxExisting);
        }

        /**
        * @brief Gets the next unused value of an Enum
        * @tparam E - The enum to allocate a new value.
        * 
        * @throws std::exception If the enum has not been registered yet with EnumAllocator::RegisterEnum()
        * @throws std::exception If the underlying type can no longer support higher values.
        */
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
            if (it->second == mUnderlyingLimit) {
                Assert("Tried to allocate another value for enum '{}', however the maximum limit for the underlying type", typeid(E).name());
            }

            // Increase and return back
            return static_cast<E>(++it->second);
        }

    private:
        std::map<HashType64, uint64_t> mEnumsToCurrent;

        friend class AmethystRuntime;
    };
} // namespace Amethyst

