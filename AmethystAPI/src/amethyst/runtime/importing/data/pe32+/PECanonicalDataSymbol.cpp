#include "amethyst/runtime/importing/data/pe32+/PECanonicalDataSymbol.hpp"

namespace Amethyst::Importing::PE {
	std::string PECanonicalDataSymbol::GetFormatType() const {
		return "pe32+";
	}

	std::string PECanonicalDataSymbol::GetKind() const {
		return "data";
	}

	std::string PECanonicalDataSymbol::ToString() const {
		std::stringstream fields;
		if (IsVirtualTable) {
			fields << "VirtualTable, ";
		}
		fields << std::format("Address[{:x}]", Address);
		return std::format("{} -> PECanonicalDataSymbol[{}]", CanonicalSymbol::ToString(), fields.str());
	}

	uintptr_t PECanonicalDataSymbol::Compute(const ResolutionContext& ctx) {
		if (ctx.ModuleHandle == nullptr) {
			Assert(false, "Cannot resolve data symbol '{}' without a valid module handle", Name);
			return 0x0;
		}

		if (IsSignature) {
			auto scanResult = SigScanSafe(Signature);
			Assert(scanResult.has_value(), "Failed to resolve signature for data '{}': {}", Name, Signature);
			return GetEffectiveAddress(*scanResult);
		}

		return GetEffectiveAddress(SlideAddress(Address));
	}

	bool PECanonicalDataSymbol::Resolve(const ResolutionContext& ctx) {
		if (IsShadow) {
			// Shadow symbols do not need to be resolved
			return true;
		}

		if (TargetOffset == 0x0) {
			Assert(false, "Data symbol '{}' has no target offset to write to", Name);
			return false;
		}

		uintptr_t base = reinterpret_cast<uintptr_t>(ctx.ModuleHandle);
		uintptr_t computedAddress = Compute(ctx);
		if (HasStorage) {
			if (StorageOffset == 0x0) {
				Assert(false, "Data symbol '{}' has storage enabled but no storage offset", Name);
				return false;
			}

			// First, write the computed address to the storage
			uintptr_t* storage = reinterpret_cast<uintptr_t*>(base + StorageOffset);
			InterlockedExchange(storage, computedAddress);

			// Now, write the address of the storage to the target
			computedAddress = reinterpret_cast<uintptr_t>(storage);
		}

		DWORD oldProtection;
		UnprotectMemory(base + TargetOffset, sizeof(void*), &oldProtection);
		uintptr_t* target = reinterpret_cast<uintptr_t*>(base + TargetOffset);
		InterlockedExchange(target, computedAddress);
		ProtectMemory(base + TargetOffset, sizeof(void*), oldProtection, nullptr);
		return true;
	}
}