#pragma once

enum class StorageVersion : int {
	Unknown, 
	OldV1, 
	OldV2, 
	OldV3, 
	LevelDB1, 
	LevelDBSubChunks, 
	LevelDBSubChunkRawZip, 
	LevelDBPaletted1, 
	LevelDBPalettedMultiBlockStorage, 
	LevelDataUpgradedSeed, 
	LevelDataStrictSize
};