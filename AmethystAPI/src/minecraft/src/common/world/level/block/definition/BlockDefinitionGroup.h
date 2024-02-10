#pragma once

class BlockDefinitionGroup {
public:
	std::byte padding0[312];
	short mLastBlockId;

	// 1.20.51.1 - 48 89 5C 24 ? 48 89 6C 24 ? 56 57 41 54 41 56 41 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 4C 8B F9
	void registerBlocks();
};
