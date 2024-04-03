#pragma once
#include <string>

namespace mce {
    class UUID {
    public:
        static UUID EMPTY;
        static size_t STRING_LENGTH;
    private:
        uint64_t Data[2];

    public:
        UUID() {
            Data[0] = 0;
            Data[1] = 0;
        }

        UUID(uint64_t mostSignificantBits, uint64_t leastSignificantBits) {

            Data[0] = mostSignificantBits;
            Data[1] = leastSignificantBits;
        }

        static UUID fromString(const std::string&);

        uint64_t getMostSignificantBits() const {
            return Data[0];
        }

        uint64_t getLeastSignificantBits() const {
            return Data[1];
        }

        std::string asString() const;

        bool operator<(const UUID& rhs) const {
            return std::make_tuple(Data[0], Data[1]) < std::make_tuple(rhs.Data[0], rhs.Data[1]);
        }

        bool operator==(const UUID& rhs) const {
            return (Data[0] == rhs.Data[0]) && (Data[1] == rhs.Data[1]);
        }

        bool operator!=(const UUID& rhs) const {
            return !(*this == rhs);
        }

        size_t getHash() const {
            return (getLeastSignificantBits() * 0x1F1F1F1F) ^ getMostSignificantBits();
        }

        bool isEmpty() const;
    };
}