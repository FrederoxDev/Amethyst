#include "amethyst/runtime/importing/data/pe32+/PECanonicalFunctionSymbol.hpp"
#include "amethyst/runtime/importing/data/pe32+/PECanonicalDataSymbol.hpp"
#include "amethyst/runtime/importing/data/CanonicalHeader.hpp"
#include <amethyst/Memory.hpp>
#include <libhat/Scanner.hpp>

namespace Amethyst::Importing::PE {
	std::string PECanonicalFunctionSymbol::GetKind() const {
		return "function";
	}

	std::string PECanonicalFunctionSymbol::ToString() const {
		std::stringstream fields;
		if (IsVirtual) {
			std::string vtName = DebugVirtualTable.empty() ? std::format("#{:016x}", VirtualTableHash) : DebugVirtualTable;
			fields << std::format("Virtual[{}, {}]", VirtualIndex, vtName);
		}
		else if (IsSignature) {
			fields << std::format("Signature[{} elements]", Signature.size());
		}
		else {
			fields << std::format("Address[{:x}]", Address);
		}
		return std::format("{} -> PECanonicalFunctionSymbol[{}]", CanonicalSymbol::ToString(), fields.str());
	}

	uintptr_t PECanonicalFunctionSymbol::Compute(const ResolutionContext& ctx) {
		if (ctx.ModuleHandle == nullptr) {
			Log::Error("Cannot resolve function symbol '{}' without a valid module handle", DisplayName());
			return 0x0;
		}

		if (IsVirtual) {
			auto it = std::find_if(
				ctx.Header->Symbols.begin(),
				ctx.Header->Symbols.end(),
				[&](const std::unique_ptr<CanonicalSymbol>& sym) {
					if (sym->GetKind() != "data" || sym->NameHash != VirtualTableHash || !sym->IsShadow)
						return false;
					auto* transformedSym = sym->Transform<PE::PECanonicalDataSymbol>();
					return transformedSym->IsVirtualTable;
				}
			);

			if (it == ctx.Header->Symbols.end()) {
				std::string vtName = DebugVirtualTable.empty() ? std::format("#{:016x}", VirtualTableHash) : DebugVirtualTable;
				Log::Error("Failed to find virtual table '{}' for function '{}'", vtName, DisplayName());
				return 0x0;
			}

			uintptr_t* vtable = reinterpret_cast<uintptr_t*>((*it)->Compute(ctx));
			if (vtable == nullptr) return 0x0;
			return vtable[VirtualIndex];
		}

		if (IsSignature) {
			const auto begin = reinterpret_cast<std::byte*>(GetMinecraftBaseAddress());
			const auto end = begin + GetMinecraftSize();
			const auto result = hat::find_pattern(begin, end, Signature);
			if (!result.has_result()) {
				Log::Error("Failed to resolve signature for function '{}' ({} elements)", DisplayName(), Signature.size());
				return 0x0;
			}
			return GetEffectiveAddress(reinterpret_cast<uintptr_t>(result.get()));
		}

		return SlideAddress(Address);
	}

	bool PECanonicalFunctionSymbol::Resolve(const ResolutionContext& ctx) {
		if (IsShadow) {
			return true;
		}

		if (TargetOffset == 0x0) {
			Log::Error("Function symbol '{}' has no target offset to write to", DisplayName());
			return false;
		}

		uintptr_t base = reinterpret_cast<uintptr_t>(ctx.ModuleHandle);
		uintptr_t computedAddress = Compute(ctx);
		if (computedAddress == 0x0) {
			Log::Error("Failed to compute address for '{}'", DisplayName());
			return false;
		}

		if (HasStorage) {
			if (StorageOffset == 0x0) {
				Log::Error("Function symbol '{}' has storage enabled but no storage offset", DisplayName());
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
