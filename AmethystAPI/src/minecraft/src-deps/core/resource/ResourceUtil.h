#pragma once

enum class ResourceFileSystem : int {
    UserPackage,
    AppPackage,
    Raw,
    RawPersistent,
    SettingsDir,
    ExternalDir,
    ServerPackage,
    DataDir,
    UserDir,
    ScreenshotsDir,
    StoreCache,
    Invalid
};