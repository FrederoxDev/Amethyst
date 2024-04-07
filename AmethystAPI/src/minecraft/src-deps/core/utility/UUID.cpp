#include "minecraft/src-deps/core/utility/UUID.hpp"
#include <iomanip>
#include <regex>
#include <sstream>


namespace mce {
	UUID UUID::EMPTY;
	size_t UUID::STRING_LENGTH = 36;

    UUID UUID::fromString(const std::string& in) {
		uint64_t mostSignificantBits = 0, leastSignificantBits = 0;
		int count = 0;

		static std::regex UUIDRegex("[a-fA-F0-9]{8}-[a-fA-F0-9]{4}-[a-fA-F0-9]{4}-[a-fA-F0-9]{4}-[a-fA-F0-9]{12}");
		std::smatch regexMatch;
		if (std::regex_search(in, regexMatch, UUIDRegex) &&
			in.length() == regexMatch[0].length()) {
			for (uint32_t i = 0; i < in.length(); ++i) {
				char c = in[i];
				uint64_t ca = 0;

				if (c >= '0' && c <= '9') {
					ca = c - '0';
				}
				else if (c >= 'a' && c <= 'f') {
					ca = c - 'a' + 10;
				}
				else if (c >= 'A' && c <= 'F') {
					ca = c - 'A' + 10;
				}
				else if (c == '-') {
					continue;
				}
				else {
					break; //invalid character
				}

				if (++count > 16) {
					leastSignificantBits |= ca << (0x80 - (4 * count));
				}
				else {
					mostSignificantBits |= ca << (0x40 - (4 * count));
				}
			}
		}

		return { mostSignificantBits, leastSignificantBits };
    }

    std::string UUID::asString() const {
        std::stringstream stream;
        stream << std::setfill('0') << std::setw(8) << std::hex << uint32_t(getMostSignificantBits() >> 32)  << '-';
        stream << std::setfill('0') << std::setw(4) << std::hex << uint16_t(getMostSignificantBits() >> 16)  << '-';
        stream << std::setfill('0') << std::setw(4) << std::hex << uint16_t(getMostSignificantBits())        << '-';
        stream << std::setfill('0') << std::setw(4) << std::hex << uint16_t(getLeastSignificantBits() >> 48) << '-';
        stream << std::setfill('0') << std::setw(8) << std::hex << uint32_t(getLeastSignificantBits() >> 16);
        stream << std::setfill('0') << std::setw(8) << std::hex << uint16_t(getLeastSignificantBits());

        return stream.str();
    }

    bool UUID::isEmpty() const {
		return *this == EMPTY;
    }
}