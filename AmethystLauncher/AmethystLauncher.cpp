// AmethystLauncher.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <Windows.h>

int main()
{
    LPCSTR dllPath = "C:\\Users\\Freddie\\Documents\\Amethyst\\AmethystAPI\\x64\\Release\\AmethystAPI.dll";

	HWND hwnd = FindWindowExW(FindWindowW(L"ApplicationFrameWindow", L"Minecraft"), NULL, NULL, L"Minecraft");
	if (hwnd == nullptr) {
		std::cout << "Could not find Minecraft" << std::endl;
		std::cin.get();
		return 1;
	}

	DWORD procID;
	GetWindowThreadProcessId(hwnd, &procID);
	HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);

	LPVOID pDllPath = VirtualAllocEx(handle, 0, strlen(dllPath) + 1, MEM_COMMIT, PAGE_READWRITE);
	WriteProcessMemory(handle, pDllPath, (LPVOID)dllPath, strlen(dllPath) + 1, 0);
	HANDLE hLoadThread = CreateRemoteThread(handle, 0, 0,
		(LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandleA("Kernel32.dll"), "LoadLibraryA"), pDllPath, 0, 0);

	WaitForSingleObject(hLoadThread, INFINITE);

	VirtualFreeEx(handle, pDllPath, strlen(dllPath) + 1, MEM_RELEASE);
	return 0;
}   