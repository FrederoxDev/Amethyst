#include "amethyst/Log.hpp"
#include "amethyst/runtime/ModContext.hpp"
#include <filesystem>
#include <chrono>

namespace Log {
    FILE* fp;
    static std::ofstream gLogFile;
    static std::mutex gLogMutex;

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
        std::strftime(filename, sizeof(filename), "%Y-%m-%d_%H-%M-%S.log", &tm);

        gLogFile.open(logDir / filename, std::ios::out | std::ios::trunc);
    }

    void ShutdownFileLogging()
    {
        std::lock_guard lock(gLogMutex);
        if (gLogFile.is_open()) gLogFile.close();
    }

    void WriteToFile(const std::string& message)
    {
        std::lock_guard lock(gLogMutex);
        if (gLogFile.is_open()) {
            gLogFile << message << "\n";
            gLogFile.flush();
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