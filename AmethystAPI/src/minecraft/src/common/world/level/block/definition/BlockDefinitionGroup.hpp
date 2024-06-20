#pragma once

class BlockDefinitionGroup {
public:
	std::byte padding0[312];
	short mLastBlockId;

	// 1.21.0.3 - 48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 54 41 55 41 56 41 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 45 33 E4
	void registerBlocks();
};
