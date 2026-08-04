#include "Mod.hpp"
#include <fstream>
#include <amethyst/runtime/ModContext.hpp>

namespace Amethyst {
Mod::Mod(const std::shared_ptr<const ModInfo>& info) : 
    mInfo(info)
{
}

Mod::Mod(Mod&& other) noexcept :
    mInfo(std::move(other.mInfo)),
    mImporter(std::move(other.mImporter)),
    mHandle(std::move(other.mHandle)),
    mIsLoaded(std::move(other.mIsLoaded))
{
}

Mod::~Mod()
{
    if (IsLoaded())
        Unload();
}

std::optional<ModError> Mod::Load()
{
    if (IsLoaded())
        return std::nullopt;

	auto& platform = Amethyst::GetPlatform();
    fs::path dllPath = mInfo->Directory / platform.GetPlatformFolderName() / mInfo->LibraryName;

    // Loads the mod in a temporary directory if it's not a runtime so that the original DLL can still be built to
    if (!mInfo->IsRuntime)
        dllPath = GetTemporaryLibrary(*mInfo);

    HMODULE handle = LoadLibraryExA(dllPath.string().c_str(), nullptr, LOAD_WITH_ALTERED_SEARCH_PATH);

    mHandle.Reset(handle);
    if (!mHandle) {
        DWORD errorCode = GetLastError();
        ModError error;
        error.Step = ModErrorStep::Loading;
        error.Type = ModErrorType::Unknown;
        error.UUID = mInfo->UUID;
        error.Message = "Failed to load '{dll}', unknown error code: 0x{error}";
        error.Data["{dll}"] = dllPath.string();
        error.Data["{error}"] = std::to_string(errorCode);
        switch (errorCode) {
        case ERROR_ACCESS_DENIED:
            error.Step = ModErrorStep::Loading;
            error.Type = ModErrorType::IOError;
            error.UUID = mInfo->UUID;
            error.Message = "'{dll}' does not have the required privileges!";
            error.Data["{dll}"] = dllPath.string();
            break;
        case ERROR_MOD_NOT_FOUND:
            error.Step = ModErrorStep::Loading;
            error.Type = ModErrorType::IOError;
            error.UUID = mInfo->UUID;
            error.Message = "'{dll}' could not be found!";
            error.Data["{dll}"] = dllPath.string();
            break;
        default:
            error.Step = ModErrorStep::Loading;
            error.Type = ModErrorType::IOError;
            error.UUID = mInfo->UUID;
            error.Message = "Failed to load '{dll}', error code: 0x{error}";
            error.Data["{dll}"] = dllPath.string();
            error.Data["{error}"] = std::to_string(errorCode);
            break;
        }
        return error;
    }

    mImporter = Importing::PE::PEImporter::Create(mHandle);
    if (mImporter)
        mImporter->ResolveAll();
    mIsLoaded = true;
    return std::nullopt;
}

void Mod::Unload()
{
    if (!IsLoaded())
        return;

    mImporter.reset();
    mHandle.Reset();
    mIsLoaded = false;
}

const ModuleHandle& Mod::GetHandle() const
{
    return mHandle;
}

Importing::Importer* Mod::GetImporter() const
{
	return mImporter.get();
}

Mod::InitializeFunction Mod::GetInitializeFunction()
{
    if (mInitializeFunction != nullptr)
        return mInitializeFunction;
    mInitializeFunction = GetFunction<InitializeFunction>("Initialize");
    return mInitializeFunction;
}

std::optional<ModError> Mod::CallInitialize(AmethystContext& ctx)
{
    try {
        if (mIsInitialized)
            return std::nullopt;
        auto initFunc = GetInitializeFunction();
        if (initFunc != nullptr) {
            initFunc(ctx, *this);
            mIsInitialized = true;
        }
    }
    catch (const std::exception& e) {
        ModError error;
        error.Step = ModErrorStep::Loading;
        error.Type = ModErrorType::UnhandledException;
        error.UUID = mInfo->UUID;
        error.Message = "An unhandled exception occurred while initializing the mod: {exception}";
        error.Data["{exception}"] = e.what();
        return error;
    }
    catch (...) {
        ModError error;
        error.Step = ModErrorStep::Loading;
        error.Type = ModErrorType::UnhandledException;
        error.UUID = mInfo->UUID;
        error.Message = "An unknown unhandled exception occurred while initializing the mod.";
        return error;
    }
    return std::nullopt;
}

bool Mod::IsLoaded() const
{
    return mIsLoaded;
}

bool Mod::operator==(const Mod& other) const
{
    return mInfo == other.mInfo;
} 

std::shared_ptr<const ModInfo> Amethyst::Mod::GetInfo(const fs::path& modDirectory)
{
    fs::path modConfigPath = modDirectory / "mod.json";
    Assert(fs::exists(modConfigPath), "mod.json could not be found, at '{}'", modConfigPath.generic_string());

    auto result = ModInfo::FromFile(modConfigPath);
	if (!result.has_value()) {
		ModError& error = result.error();
		Log::Error("{}", error.getFormattedMessage());
		AssertFail("Failed to load mod info at '{}'", modConfigPath.generic_string());
	}

    return std::make_shared<const Amethyst::ModInfo>(std::move(*result));
}

fs::path Mod::GetTemporaryLibrary(const ModInfo& info)
{
    Amethyst::Platform& platform = Amethyst::GetPlatform();

    // Ensure temp directory exists
    fs::path tempDir = platform.GetAmethystFolder() / L"Temp" / info.GetVersionedName();
    if (!fs::exists(tempDir)) fs::create_directories(tempDir);

    fs::path sourceDir = info.Directory / platform.GetPlatformFolderName();
    fs::path originalDll = sourceDir / info.LibraryName;
    Assert(fs::exists(originalDll), "Could not find '{}'", originalDll.generic_string());

    fs::path tempDll = tempDir / info.LibraryName;

	try {
        for (const auto& entry : fs::directory_iterator(sourceDir)) {
            if (!entry.is_regular_file()) continue;
            if (entry.path().extension() != ".dll") continue;
            fs::path dst = tempDir / entry.path().filename();
            fs::copy_file(entry.path(), dst, fs::copy_options::overwrite_existing);
        }
    }
    catch (const std::filesystem::filesystem_error& e) {
        Assert(false, "{} (Error code: {})", e.what(), e.code().value());
    }

    return tempDll;
}
} // namespace Amethyst