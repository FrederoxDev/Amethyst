#include "amethyst/runtime/importing/data/pe32+/PECanonicalFunctionSymbol.hpp"
#include "amethyst/runtime/importing/data/pe32+/PECanonicalDataSymbol.hpp"
#include "amethyst/runtime/importing/data/CanonicalHeader.hpp"
#include <amethyst/Memory.hpp>

namespace Amethyst::Importing::PE {
	std::string PECanonicalFunctionSymbol::GetFormatType() const {
		return "pe32+";
	}

	std::string PECanonicalFunctionSymbol::GetKind() const {
		return "function";
	}

	std::string PECanonicalFunctionSymbol::ToString() const {
		std::stringstream fields;
		if (IsVirtual) {
			fields << std::format("Virtual[{}, {}]", VirtualIndex, VirtualTable);
		}
		else if (IsSignature) {
			fields << std::format("Signature[{}]", Signature);
		}
		else {
			fields << std::format("Address[{:x}]", Address);
		}
		return std::format("{} -> PECanonicalFunctionSymbol[{}]", CanonicalSymbol::ToString(), fields.str());
	}

	uintptr_t PECanonicalFunctionSymbol::Compute(const ResolutionContext& ctx) {
		if (ctx.ModuleHandle == nullptr) {
			Assert(false, "Cannot resolve function symbol '{}' without a valid module handle", Name);
			return 0x0;
		}

		if (IsVirtual) {
			auto it = std::find_if(
				ctx.Header->Symbols.begin(),
				ctx.Header->Symbols.end(),
				[&](const std::unique_ptr<CanonicalSymbol>& sym) {
					if (sym->GetFormatType() != "pe32+" || sym->GetKind() != "data" || sym->Name != VirtualTable || !sym->IsShadow)
						return false;
					auto* transformedSym = sym->Transform<PE::PECanonicalDataSymbol>();
					return transformedSym->IsVirtualTable;
				}
			);

			if (it == ctx.Header->Symbols.end()) {
				Assert(false, "Failed to find virtual table '{}' for function '{}'", VirtualTable, Name);
				return 0x0;
			}

			uintptr_t* vtable = reinterpret_cast<uintptr_t*>((*it)->Compute(ctx));
			return vtable[VirtualIndex];
		}
		
		if (IsSignature) {
			auto scanResult = SigScanSafe(Signature);
			Assert(scanResult.has_value(), "Failed to resolve signature for function '{}': {}", Name, Signature);
			return GetEffectiveAddress(*scanResult);
		}

		return GetEffectiveAddress(SlideAddress(Address));
	}

	bool PECanonicalFunctionSymbol::Resolve(const ResolutionContext& ctx) {
		if (IsShadow) {
			// Shadow symbols do not need to be resolved
			return true;
		}

		if (TargetOffset == 0x0) {
			Assert(false, "Function symbol '{}' has no target offset to write to", Name);
			return false;
		}

		uintptr_t base = reinterpret_cast<uintptr_t>(ctx.ModuleHandle);
		uintptr_t computedAddress = Compute(ctx);
		Assert(computedAddress != 0x0, "Failed to compute address for '{}'", Name);

		if (HasStorage) {
			if (StorageOffset == 0x0) {
				Assert(false, "Function symbol '{}' has storage enabled but no storage offset", Name);
				return false;
			}

			// Virtual destructors need special handling
			if (IsDestructor && IsVirtual) {
				// First, write the computed address to the storage
				// We add 2 to the storage offset to skip "mov, rax, imm64" instruction
				uintptr_t* storageAddr = reinterpret_cast<uintptr_t*>(base + StorageOffset + 2);
				InterlockedExchange(storageAddr, computedAddress);

				// Now, write the address of the storage to the target
				computedAddress = base + StorageOffset;
			}
		}

		DWORD oldProtection;
		UnprotectMemory(base + TargetOffset, sizeof(void*), &oldProtection);
		InterlockedExchange(reinterpret_cast<volatile uintptr_t*>(base + TargetOffset), computedAddress);
		ProtectMemory(base + TargetOffset, sizeof(void*), oldProtection, nullptr);
		return true;
	}
}