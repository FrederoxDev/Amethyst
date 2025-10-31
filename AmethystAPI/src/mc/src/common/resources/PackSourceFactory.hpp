#pragma once
#include "mc/src-deps/core/file/Path.hpp"
#include "mc/src-deps/core/resource/ResourceHelper.hpp"
#include "mc/src/common/resources/DirectoryPackSource.hpp"

class PackSourceFactory {
public:
#if CLIENT
    virtual void unknown0();
    virtual void unknown1();
	virtual void unknown2();
	virtual void unknown3();
    virtual void unknown4();
    virtual void unknown5();
    virtual void unknown6();
    virtual void unknown7();
    virtual DirectoryPackSource& createDirectoryPackSource(const Core::Path& path, PackType type, PackOrigin origin, bool isDevDirectory);
#else
	virtual void unknown0();
	virtual void unknown1();
	virtual void unknown2();
	virtual DirectoryPackSource& createDirectoryPackSource(const Core::Path& path, PackType type, PackOrigin origin, bool isDevDirectory);
	virtual void unknown4();
	virtual void unknown5();
	virtual void unknown6();
	virtual void unknown7();
#endif
};