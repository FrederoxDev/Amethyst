#pragma once
#include "amethyst/runtime/importing/data/CanonicalSymbol.hpp"
#include <libhat/signature.hpp>

namespace Amethyst::Importing::PE {
	class PECanonicalFunctionSymbol :
		public CanonicalSymbol
	{
	public:
		uint32_t TargetOffset = 0x0;
		bool HasStorage = false;
		uint32_t StorageOffset = 0x0;
		bool IsDestructor = false;
		bool IsVirtual = false;
		uint32_t VirtualIndex = 0;
		uint64_t VirtualTableHash = 0;
		std::string DebugVirtualTable = "";
		bool IsSignature = false;
		hat::signature Signature = {};
		uint64_t Address = 0x0;

		virtual std::string GetKind() const override;
		virtual std::string ToString() const override;
		virtual uintptr_t Compute(const ResolutionContext& ctx) override;
		virtual bool Resolve(const ResolutionContext& ctx) override;
	};
}
