#include "amethyst/runtime/importing/data/pe32+/PECanonicalHeader.hpp"
#include "amethyst/runtime/importing/data/pe32+/PECanonicalFunctionSymbol.hpp"
#include "amethyst/runtime/importing/data/pe32+/PECanonicalDataSymbol.hpp"
#include "amethyst/runtime/utility/SimpleBinaryReader.hpp"
#include <libhat/signature.hpp>

namespace Amethyst::Importing::PE {
	std::string PECanonicalHeader::ToString() const {
		return std::format("{} -> PECanonicalHeader[IDT: {:x}, IDT Size: {:x}, Import Count: {}]", CanonicalHeader::ToString(), OldIDT, OldIDTSize, ImportCount);
	}

	std::unique_ptr<PECanonicalHeader> PECanonicalHeader::ReadFrom(Amethyst::SimpleBinaryReader& reader) {
		// Magic
		std::string magic = reader.ReadPrefixedString();
		Assert(magic == "AME_RTI", "Invalid RTIH magic: '{}'", magic);

		// Version
		uint32_t version = reader.Read<uint32_t>();
		Assert(version == 2, "Unsupported RTIH format version: {}", version);

		// Flags
		uint32_t flags = reader.Read<uint32_t>();
		bool hasDebugNames = (flags & 1) != 0;

		// Symbol count
		uint32_t symbolCount = reader.Read<uint32_t>();

		auto header = std::make_unique<PECanonicalHeader>();
		header->HasDebugNames = hasDebugNames;

		for (uint32_t i = 0; i < symbolCount; i++) {
			// Common prefix
			uint8_t kind = reader.Read<uint8_t>();
			uint64_t nameHash = reader.Read<uint64_t>();
			std::string debugName = "";
			if (hasDebugNames) {
				debugName = reader.ReadPrefixedString();
			}
			uint32_t targetOffset = reader.Read<uint32_t>();
			bool hasStorage = reader.Read<uint8_t>() != 0;
			uint32_t storageOffset = reader.Read<uint32_t>();

			if (kind == 0) {
				// Function symbol
				auto sym = std::make_unique<PECanonicalFunctionSymbol>();
				sym->NameHash = nameHash;
				sym->DebugName = debugName;
				sym->TargetOffset = targetOffset;
				sym->HasStorage = hasStorage;
				sym->StorageOffset = storageOffset;

				sym->IsDestructor = reader.Read<uint8_t>() != 0;
				sym->IsVirtual = reader.Read<uint8_t>() != 0;

				if (sym->IsVirtual) {
					sym->VirtualIndex = reader.Read<uint32_t>();
					sym->VirtualTableHash = reader.Read<uint64_t>();
					if (hasDebugNames) {
						sym->DebugVirtualTable = reader.ReadPrefixedString();
					}
				} else {
					sym->IsSignature = reader.Read<uint8_t>() != 0;
					if (sym->IsSignature) {
						// Read pre-compiled signature
						uint32_t count = reader.Read<uint32_t>();
						sym->Signature.reserve(count);
						for (uint32_t j = 0; j < count; j++) {
							uint8_t val = reader.Read<uint8_t>();
							uint8_t present = reader.Read<uint8_t>();
							if (present) {
								sym->Signature.push_back(hat::signature_element(static_cast<std::byte>(val)));
							} else {
								sym->Signature.push_back(hat::signature_element(std::nullopt));
							}
						}
					} else {
						sym->Address = reader.Read<uint64_t>();
					}
				}

				if (sym->IsDestructor && sym->IsVirtual) {
					sym->HasStorage = true;
				}
				sym->IsShadow = false;
				header->Symbols.push_back(std::move(sym));
			}
			else if (kind == 1) {
				// Data symbol
				auto sym = std::make_unique<PECanonicalDataSymbol>();
				sym->NameHash = nameHash;
				sym->DebugName = debugName;
				sym->TargetOffset = targetOffset;
				sym->HasStorage = hasStorage;
				sym->StorageOffset = storageOffset;

				sym->IsVirtualTableAddress = reader.Read<uint8_t>() != 0;
				sym->IsVirtualTable = reader.Read<uint8_t>() != 0;
				sym->IsSignature = reader.Read<uint8_t>() != 0;

				if (sym->IsSignature) {
					uint32_t count = reader.Read<uint32_t>();
					sym->Signature.reserve(count);
					for (uint32_t j = 0; j < count; j++) {
						uint8_t val = reader.Read<uint8_t>();
						uint8_t present = reader.Read<uint8_t>();
						if (present) {
							sym->Signature.push_back(hat::signature_element(static_cast<std::byte>(val)));
						} else {
							sym->Signature.push_back(hat::signature_element(std::nullopt));
						}
					}
				} else {
					sym->Address = reader.Read<uint64_t>();
				}

				sym->IsShadow = sym->IsVirtualTable;
				header->Symbols.push_back(std::move(sym));
			}
			else {
				AssertFail("Unknown symbol kind tag: {}", kind);
			}
		}

		// PE-specific trailer
		header->OldIDT = reader.Read<uint32_t>();
		header->OldIDTSize = reader.Read<uint32_t>();
		header->ImportCount = reader.Read<uint32_t>();

		return header;
	}
}
