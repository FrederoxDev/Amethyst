#include "amethyst/Log.hpp"
#include "amethyst/runtime/ModContext.hpp"
#include <filesystem>
#include <chrono>

namespace Log {
    FILE* fp;
    static HANDLE gLogHandle = nullptr;
    static HANDLE gJsonHandle = nullptr;
    static std::mutex gLogMutex;
    static std::string gSessionId;

    constexpr const wchar_t* kLogPathEnvVar = L"AMETHYST_LOG_PATH";
    constexpr const wchar_t* kJsonPathEnvVar = L"AMETHYST_JSON_PATH";
    constexpr const char* kSessionEnvVarA = "AMETHYST_LOG_SESSION";

    static HANDLE OpenAppendHandle(const std::filesystem::path& path, DWORD creationDisposition)
    {
        return CreateFileW(
            path.c_str(),
            FILE_APPEND_DATA,
            FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
            nullptr,
            creationDisposition,
            FILE_ATTRIBUTE_NORMAL | FILE_FLAG_WRITE_THROUGH,
            nullptr);
    }

    static void EnsureHandlesOpen()
    {
        if (!gLogHandle) {
            wchar_t path[MAX_PATH];
            if (GetEnvironmentVariableW(kLogPathEnvVar, path, MAX_PATH) > 0) {
                gLogHandle = OpenAppendHandle(path, OPEN_ALWAYS);
            }
        }

        if (!gJsonHandle) {
            wchar_t path[MAX_PATH];
            if (GetEnvironmentVariableW(kJsonPathEnvVar, path, MAX_PATH) > 0) {
                gJsonHandle = OpenAppendHandle(path, OPEN_ALWAYS);
            }
        }

        if (gSessionId.empty()) {
            char session[64];
            DWORD len = GetEnvironmentVariableA(kSessionEnvVarA, session, sizeof(session));
            if (len > 0) gSessionId = std::string(session, len);
        }
    }

    static void WriteHandle(HANDLE handle, const std::string& text)
    {
        if (!handle || handle == INVALID_HANDLE_VALUE) return;
        DWORD written = 0;
        WriteFile(handle, text.data(), static_cast<DWORD>(text.size()), &written, nullptr);
    }

    static std::string NowIso8601Utc()
    {
        auto now = std::chrono::system_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
        auto time = std::chrono::system_clock::to_time_t(now);
        std::tm tm{};
        gmtime_s(&tm, &time);
        char buf[32];
        std::strftime(buf, sizeof(buf), "%Y-%m-%dT%H:%M:%S", &tm);
        return std::format("{}.{:03}Z", std::string(buf), ms.count());
    }

    static std::string JsonEscape(const std::string& value)
    {
        std::string out;
        out.reserve(value.size());
        for (char c : value) {
            switch (c) {
                case '"': out += "\\\""; break;
                case '\\': out += "\\\\"; break;
                case '\n': out += "\\n"; break;
                case '\r': out += "\\r"; break;
                case '\t': out += "\\t"; break;
                default:
                    if (static_cast<unsigned char>(c) < 0x20) out += std::format("\\u{:04x}", static_cast<unsigned char>(c));
                    else out += c;
            }
        }
        return out;
    }

    void InitializeFileLogging()
    {
        char appdata[MAX_PATH];
        GetEnvironmentVariableA("APPDATA", appdata, MAX_PATH);
        std::filesystem::path logDir = std::filesystem::path(appdata) / "Amethyst" / "Launcher" / "Logs";
        std::filesystem::create_directories(logDir);

        // Filename with timestamp
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        std::tm tm{};
        localtime_s(&tm, &time);
        char filename[64];
        std::strftime(filename, sizeof(filename), "%Y-%m-%d_%H-%M-%S", &tm);
        gSessionId = filename;

        std::filesystem::path logPath = logDir / (gSessionId + ".log");
        std::filesystem::path jsonPath = logDir / (gSessionId + ".jsonl");

        gLogHandle = OpenAppendHandle(logPath, CREATE_ALWAYS);
        gJsonHandle = OpenAppendHandle(jsonPath, CREATE_ALWAYS);

        SetEnvironmentVariableW(kLogPathEnvVar, logPath.c_str());
        SetEnvironmentVariableW(kJsonPathEnvVar, jsonPath.c_str());
        SetEnvironmentVariableA(kSessionEnvVarA, gSessionId.c_str());
    }

    void ShutdownFileLogging()
    {
        std::lock_guard lock(gLogMutex);
        if (gLogHandle) { CloseHandle(gLogHandle); gLogHandle = nullptr; }
        if (gJsonHandle) { CloseHandle(gJsonHandle); gJsonHandle = nullptr; }
    }

    void WriteToFile(const std::string& level, const std::string& thread, const std::string& mod, const std::string& message, const std::string& humanLine)
    {
        std::lock_guard lock(gLogMutex);
        EnsureHandlesOpen();
        std::string timestamp = NowIso8601Utc();

        if (gLogHandle) {
            std::string line = std::format("{} {}\r\n", timestamp, humanLine);
            WriteHandle(gLogHandle, line);
        }

        if (gJsonHandle) {
            std::string json = std::format(
                "{{\"timestamp\":\"{}\",\"session\":\"{}\",\"level\":\"{}\",\"thread\":\"{}\",\"source\":\"{}\",\"message\":\"{}\"}}\r\n",
                timestamp, gSessionId, level, JsonEscape(thread), JsonEscape(mod), JsonEscape(message));
            WriteHandle(gJsonHandle, json);
        }
    }

    void InitializeConsole()
    {
        // Initialize console with stdout/stderr
        AllocConsole();
        freopen_s(&fp, "CONOUT$", "w", stdout);
        freopen_s(&fp, "CONOUT$", "w", stderr);

        // Enable ANSI-Escape codes for colours
        HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD consoleMode;

        GetConsoleMode(consoleHandle, &consoleMode);
        consoleMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(consoleHandle, consoleMode);
        SetConsoleTitle("AmethystAPI");
    }

    void DestroyConsole()
    {
        ShutdownFileLogging();
        fclose(fp);
        FreeConsole();
    }

    void HideConsole()
    {
       HWND consoleWindow = GetConsoleWindow();
       ShowWindow(consoleWindow, SW_HIDE);
    }

    std::string GetModName() {
        const Amethyst::Mod* mod = Amethyst::GetOwnMod();
        if (mod == nullptr) {
            return "Amethyst-Runtime";
        }
        return mod->mInfo->LoggingName;
    }

    std::string GetThreadName() {
		if (!Amethyst::IsAmethystContextInitialized()) {
			return std::format("{:>7}", std::this_thread::get_id());
		}

        switch (Amethyst::GetCurrentThreadClass()) {
        case Amethyst::ThreadClass::AmethystRuntime:
            return "runtime";
        case Amethyst::ThreadClass::MainClient:
            return " client";
        case Amethyst::ThreadClass::MainServer:
            return " server";
        case Amethyst::ThreadClass::EngineNamed:
            return std::format("{:>7.7}", Amethyst::GetCurrentThreadName());
        case Amethyst::ThreadClass::Unknown:
            break;
        }

        // Fallback to thread IDs
        return std::format("{:>7}", std::this_thread::get_id());
    }
} // namespace Log