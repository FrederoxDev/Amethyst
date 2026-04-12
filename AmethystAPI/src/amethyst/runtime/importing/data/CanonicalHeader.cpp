#include "amethyst/runtime/importing/data/CanonicalHeader.hpp"
#include "amethyst/runtime/importing/data/pe32+/PECanonicalHeader.hpp"

namespace Amethyst::Importing {
	std::string CanonicalHeader::ToString() const {
		return std::format("CanonicalHeader[{} symbols]", Symbols.size());
	}

	template<>
	PE::PECanonicalHeader* CanonicalHeader::Transform<PE::PECanonicalHeader>() {
		return static_cast<PE::PECanonicalHeader*>(this);
	}
}
