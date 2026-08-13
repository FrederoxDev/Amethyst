#include "amethyst/Log.hpp"
#include "amethyst/runtime/ModContext.hpp"
#include <filesystem>
#include <chrono>
#include <share.h>

namespace Log {
    FILE* fp;
    static FILE* gLogFile = nullptr;
    static FILE* gJsonFile = nullptr;
    static std::mutex gLogMutex;
    static std::string gSessionId;

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

        gLogFile = _wfsopen(logPath.c_str(), L"w", _SH_DENYWR);
        gJsonFile = _wfsopen(jsonPath.c_str(), L"w", _SH_DENYWR);
    }

    void ShutdownFileLogging()
    {
        std::lock_guard lock(gLogMutex);
        if (gLogFile) { fclose(gLogFile); gLogFile = nullptr; }
        if (gJsonFile) { fclose(gJsonFile); gJsonFile = nullptr; }
    }

    void WriteToFile(const std::string& level, const std::string& thread, const std::string& mod, const std::string& message, const std::string& humanLine)
    {
        std::lock_guard lock(gLogMutex);
        std::string timestamp = NowIso8601Utc();

        if (gLogFile) {
            std::string line = std::format("{} {}\n", timestamp, humanLine);
            fwrite(line.data(), 1, line.size(), gLogFile);
            fflush(gLogFile);
        }

        if (gJsonFile) {
            std::string json = std::format(
                "{{\"timestamp\":\"{}\",\"session\":\"{}\",\"level\":\"{}\",\"thread\":\"{}\",\"source\":\"{}\",\"message\":\"{}\"}}\n",
                timestamp, gSessionId, level, JsonEscape(thread), JsonEscape(mod), JsonEscape(message));
            fwrite(json.data(), 1, json.size(), gJsonFile);
            fflush(gJsonFile);
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

        if (Amethyst::IsOnAmethystThread()) return "runtime";
        if (Amethyst::IsOnMainClientThread()) return " client";
        if (Amethyst::IsOnMainServerThread()) return " server";
        // Fallback to thread IDs
        return std::format("{:>7}", std::this_thread::get_id());
    }
} // namespace Log