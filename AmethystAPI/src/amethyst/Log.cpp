#include "amethyst/Log.hpp"
#include "amethyst/runtime/ModContext.hpp"

namespace Log {
    FILE* fp;

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