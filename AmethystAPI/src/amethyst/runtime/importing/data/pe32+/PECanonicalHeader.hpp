#pragma once
#include "amethyst/runtime/importing/data/CanonicalHeader.hpp"

namespace Amethyst {
	class SimpleBinaryReader;
}

namespace Amethyst::Importing::PE {
	class PECanonicalHeader :
		public CanonicalHeader
	{
	public:
		uint32_t OldIDT = 0;
		uint32_t OldIDTSize = 0;
		uint32_t ImportCount = 0;
		bool HasDebugNames = false;

		virtual std::string ToString() const override;

		static std::unique_ptr<PECanonicalHeader> ReadFrom(Amethyst::SimpleBinaryReader& reader);
	};
}
