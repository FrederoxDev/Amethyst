#pragma once
#include <functional>
#include <string>
#include "mc/src-deps/core/resource/ResourceUtil.hpp"
#include "mc/src-deps/core/semVer/SemVersion.hpp"
#include "mc/src-deps/core/utility/UUID.hpp"

enum class PackCategory : int {
	_Unknown,
	_RealmsUnknown,
	Standard,
	Premium,
	Custom,
	Subpack
};

enum class PackType : char {
	Invalid,
	Addon,
	Cached,
	CopyProtected,
	Behavior,
	PersonaPiece,
	Resources,
	Skins,
	WorldTemplate,
	Count
};

enum class PackOrigin : char {
	_Unknown,
	_RealmsUnknown,
	Package,
	Treatment,
	Dev,
	World,
	User,
	TempCache,
	PremiumCache,
	PremiumTempCache
};

struct PackIdVersion {
	mce::UUID mId;
	SemVersion mVersion;
	PackType mPackType;
};

class ResourceLocation {
public:
	ResourceFileSystem mFileSystem; // this + 0x0
	std::string mPath;              // this + 0x8
	uint64_t mPathHash;             // this + 0x28
	uint64_t mFullHash;             // this + 0x30

public:
	~ResourceLocation();
	ResourceLocation();
	ResourceLocation(const HashedString& path, ResourceFileSystem fileSystem = ResourceFileSystem::UserPackage);
	ResourceLocation(const std::string& path, ResourceFileSystem fileSystem = ResourceFileSystem::UserPackage);
	ResourceLocation(const char* path, ResourceFileSystem fileSystem = ResourceFileSystem::UserPackage);

	inline bool operator==(const ResourceLocation& rhs) const {
		return mFullHash == rhs.mFullHash;
	}

private:
	void _computeHashes();
};

namespace std {
	template<>
	struct hash<ResourceLocation> {
		std::size_t operator()(const ResourceLocation& rl) const noexcept {
			return static_cast<std::size_t>(rl.mFullHash);
		}
	};
}

static_assert(offsetof(ResourceLocation, mPath) == 8);