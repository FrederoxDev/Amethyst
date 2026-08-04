#pragma once
#include "Json.hpp"
#include <amethyst/Log.hpp>
#include <amethyst/Utility.hpp>
#include <filesystem>
#include <iostream>
#include <shlobj.h>
#include <vector>

#include "Json.hpp"

#include <amethyst/Log.hpp>
#include <amethyst/Utility.hpp>
#include <amethyst/runtime/mod/ModInfo.hpp>
#include <amethyst/runtime/mod/ModuleHandle.hpp>
#include <amethyst/runtime/importing/Importer.hpp>
#include <amethyst/runtime/importing/pe32+/PEImporter.hpp>

#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>

using json = nlohmann::json;

namespace fs = std::filesystem;

class AmethystContext;
namespace Amethyst {
class Mod {
    using InitializeFunction = void(*)(AmethystContext&, const Mod&);

    ModuleHandle mHandle;
    std::unique_ptr<Importing::Importer> mImporter;
    bool mIsLoaded = false;
    bool mIsInitialized = false;

    InitializeFunction mInitializeFunction = nullptr;
public:
    // Metadata and stuff
    std::shared_ptr<const ModInfo> mInfo;

    Mod() = delete;
    Mod(const Mod&) = delete;
    Mod& operator=(const Mod&) = delete;
    Mod& operator=(Mod&&) noexcept = delete;

    explicit Mod(const std::shared_ptr<const ModInfo>& info);
    Mod(Mod&& other) noexcept;
    ~Mod();

    std::optional<ModError> Load();
    void Unload();

    const ModuleHandle& GetHandle() const;
    Importing::Importer* GetImporter() const;

    template <typename T = FARPROC>
    T GetFunction(const char* functionName) const
    {
        return reinterpret_cast<T>(GetProcAddress(mHandle, functionName));
    }

    InitializeFunction GetInitializeFunction();
    std::optional<ModError> CallInitialize(AmethystContext& ctx);

    bool IsLoaded() const;

    bool operator==(const Mod& other) const;
    static std::shared_ptr<const ModInfo> GetInfo(const fs::path& modDirectory);
    static fs::path GetTemporaryLibrary(const ModInfo& info);
};
} // namespace Amethyst