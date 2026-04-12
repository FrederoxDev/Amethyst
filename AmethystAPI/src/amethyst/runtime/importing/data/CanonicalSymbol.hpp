#pragma once

namespace Amethyst::Importing {
	namespace PE {
		class PECanonicalDataSymbol;
		class PECanonicalFunctionSymbol;
	}

	class CanonicalHeader;
	class ResolutionContext {
	public:
		void* ModuleHandle = nullptr;
		CanonicalHeader* Header = nullptr;
	};

	class CanonicalSymbol {
	public:
		uint64_t NameHash = 0;
		std::string DebugName = "";
		bool IsShadow = false;

		virtual ~CanonicalSymbol() = default;
		virtual std::string GetKind() const = 0;
		virtual std::string ToString() const;
		virtual uintptr_t Compute(const ResolutionContext& ctx) = 0;
		virtual bool Resolve(const ResolutionContext& ctx) = 0;

		std::string DisplayName() const {
			return DebugName.empty() ? std::format("#{:016x}", NameHash) : DebugName;
		}

		template<typename T = CanonicalSymbol>
		T* Transform() {
			static_assert(!std::is_same_v<T, T>, "Transforming CanonicalSymbol to T not implemented.");
		}

		template<>
		PE::PECanonicalDataSymbol* Transform<PE::PECanonicalDataSymbol>();
		template<>
		PE::PECanonicalFunctionSymbol* Transform<PE::PECanonicalFunctionSymbol>();
	};
}
