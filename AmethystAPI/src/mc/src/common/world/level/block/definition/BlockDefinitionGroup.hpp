/// @symbolgeneration
#pragma once
#include <amethyst/Imports.hpp>

class BlockDefinitionGroup {
public:
	std::byte padding0[312];
	short mLastBlockId;
	 
	/// @signature {48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B 79 ? 48 8B F1 48 8B 1F, win-server}
	/// @signature {48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 54 41 55 41 56 41 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 45 33 E4}
	MC void registerBlocks();

	short getNextBlockId() {
		return ++mLastBlockId;
	}
};
 