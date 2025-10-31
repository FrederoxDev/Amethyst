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
    std::string versionedName = mInfo->GetVersionedName();
    fs::path dllPath = mInfo->Directory / platform.GetPlatformFolderName() / mInfo->LibraryName;

    // Loads the mod in a temporary directory if it's not a runtime so that the original DLL can still be built to
    if (!mInfo->IsRuntime)
        dllPath = GetTemporaryLibrary(versionedName);

    HMODULE handle = LoadLibrary(dllPath.string().c_str());

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

std::shared_ptr<const ModInfo> Amethyst::Mod::GetInfo(const std::string& modName)
{
    Amethyst::Platform& platform = Amethyst::GetPlatform();
    fs::path modConfigPath = platform.GetAmethystFolder() / L"mods" / modName / L"mod.json";

    Assert(fs::exists(modConfigPath), "mod.json could not be found, for '{}'", modName);

    auto result = ModInfo::FromFile(modConfigPath);
	if (!result.has_value()) {
		ModError& error = result.error();
		Log::Error("{}", error.getFormattedMessage());
		AssertFail("Failed to load mod info for '{}' at '{}'", modName, modConfigPath.generic_string());
	}
	
    return std::make_shared<const Amethyst::ModInfo>(std::move(*result));
}

fs::path Mod::GetTemporaryLibrary(const std::string& modName)
{
    std::string modShortened = modName;
    size_t atPos = modShortened.find("@");

    if (atPos != std::string::npos) {
        modShortened = modShortened.substr(0, atPos);
    }

    Amethyst::Platform& platform = Amethyst::GetPlatform();

    // Ensure temp directory exists
    fs::path tempDir = platform.GetAmethystFolder() / L"Temp" / modName;
    if (!fs::exists(tempDir)) fs::create_directories(tempDir);

    fs::path originalDll = platform.GetAmethystFolder() / L"Mods" / modName / platform.GetPlatformFolderName() / std::string(modShortened + ".dll");
    Assert(fs::exists(originalDll), "Could not find '{}.dll'", modShortened);

    fs::path tempDll = tempDir / (modShortened + ".dll");

    try {
        fs::copy_file(originalDll, tempDll, fs::copy_options::overwrite_existing);
    }
    catch (const std::filesystem::filesystem_error& e) {
        Assert(false, "{} (Error code: {})", e.what(), e.code().value());
    }

    return tempDll;
}
} // namespace Amethyst