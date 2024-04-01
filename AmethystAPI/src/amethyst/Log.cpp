#include "amethyst/Log.hpp"

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
} // namespace Log