// AmethystLauncher.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <Windows.h>

HANDLE GetOrCreateMinecraftHandle() {
	// Look for an existing Minecraft window
	HWND hwnd = FindWindowExW(FindWindowW(L"ApplicationFrameWindow", L"Minecraft"), NULL, NULL, L"Minecraft");

	if (hwnd == NULL) {
		// Create a minecraft process using its URI
		ShellExecute(0, 0, L"minecraft:", 0, 0, SW_HIDE);
		hwnd = FindWindowExW(FindWindowW(L"ApplicationFrameWindow", L"Minecraft"), NULL, NULL, L"Minecraft");
	}

	DWORD procID;
	GetWindowThreadProcessId(hwnd, &procID);
	return OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);
}

void InjectDLL(HANDLE& handle, LPCSTR& dllPath) {
	LPVOID dll = VirtualAllocEx(handle, 0, strlen(dllPath) + 1, MEM_COMMIT, PAGE_READWRITE);

	WriteProcessMemory(handle, dll, (LPVOID)dllPath, strlen(dllPath) + 1, 0);
	HANDLE hLoadThread = CreateRemoteThread(
		handle, 0, 0, (LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandleA("Kernel32.dll"), "LoadLibraryA"), dll, 0, 0
	);

	WaitForSingleObject(hLoadThread, INFINITE);
	VirtualFreeEx(handle, dll, strlen(dllPath) + 1, MEM_RELEASE);
}

int main() {
	const char* amethyst_folder = std::getenv("amethyst");
	std::string dll_path = std::string(amethyst_folder) + "/mods/AmethystRuntime/AmethystRuntime.dll";
	const char* path = dll_path.c_str();

	HANDLE handle = GetOrCreateMinecraftHandle();
	InjectDLL(handle, path);
}