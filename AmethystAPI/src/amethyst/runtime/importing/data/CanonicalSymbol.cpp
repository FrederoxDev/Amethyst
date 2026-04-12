#include "amethyst/runtime/importing/data/CanonicalSymbol.hpp"

namespace Amethyst::Importing {
	std::string CanonicalSymbol::ToString() const {
		return std::format("CanonicalSymbol[{}, {}, {}]", DisplayName(), GetKind(), IsShadow);
	}

	template<>
	PE::PECanonicalDataSymbol* CanonicalSymbol::Transform<PE::PECanonicalDataSymbol>() {
		if (GetKind() != "data") {
			Assert(false, "Cannot transform CanonicalSymbol of kind {} to PECanonicalDataSymbol", GetKind());
			return nullptr;
		}
		return reinterpret_cast<PE::PECanonicalDataSymbol*>(this);
	}

	template<>
	PE::PECanonicalFunctionSymbol* CanonicalSymbol::Transform<PE::PECanonicalFunctionSymbol>() {
		if (GetKind() != "function") {
			Assert(false, "Cannot transform CanonicalSymbol of kind {} to PECanonicalFunctionSymbol", GetKind());
			return nullptr;
		}
		return reinterpret_cast<PE::PECanonicalFunctionSymbol*>(this);
	}
}
