#include "Loader.h"

void ReportIssue(LPCWSTR message) {
    MessageBoxW(NULL, message, L"AmethystLauncher", MB_ICONERROR | MB_OK);
}

std::wstring convertStringToWString(const std::string& s) {
    return std::wstring(s.begin(), s.end());
}

DWORD GetProcessIdByName(const wchar_t* processName) {
    DWORD processId = 0;
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (snapshot != INVALID_HANDLE_VALUE) {
        PROCESSENTRY32 processEntry;
        processEntry.dwSize = sizeof(processEntry);

        if (Process32First(snapshot, &processEntry)) {
            do {
                wchar_t wideProcessName[MAX_PATH];
                MultiByteToWideChar(CP_ACP, 0, processEntry.szExeFile, -1, wideProcessName, MAX_PATH);

                if (_wcsicmp(wideProcessName, processName) == 0) {
                    processId = processEntry.th32ProcessID;
                    break;
                }
            } while (Process32Next(snapshot, &processEntry));
        }

        CloseHandle(snapshot);
    }

    return processId;
}

HANDLE getMinecraftWindowHandle() {
    DWORD procID = GetProcessIdByName(L"Minecraft.Windows.exe");
    if (procID == 0) {
        system("explorer.exe shell:appsFolder\\Microsoft.MinecraftUWP_8wekyb3d8bbwe!App");

        while (procID == 0) {
            procID = GetProcessIdByName(L"Minecraft.Windows.exe");
        }
    }

    return OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);
}

void InjectDLL(HANDLE minecraftHandle, const std::string& path) {
    LPVOID dll = VirtualAllocEx(minecraftHandle, NULL, path.length() + 1,
                                MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (dll == NULL) {
        ReportIssue(L"Failed to allocate memory for AmethystRuntime.dll");
        return;
    }
    if (!WriteProcessMemory(minecraftHandle, dll, path.c_str(),
                            path.length() + 1, NULL)) {
        ReportIssue(L"Failed to write AmethystRuntime.dll to memory");
        return;
    }

    HANDLE thread = CreateRemoteThread(minecraftHandle, NULL, NULL,
                                       (LPTHREAD_START_ROUTINE)LoadLibraryA,
                                       dll, NULL, NULL);
    if (thread == NULL) {
        ReportIssue(L"Failed to create remote thread");
        return;
    }

    WaitForSingleObject(thread, INFINITE);
    VirtualFreeEx(minecraftHandle, dll, 0, MEM_RELEASE);
}