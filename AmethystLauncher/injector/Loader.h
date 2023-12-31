#pragma once
#include <string>
#include <Windows.h>
#include <locale>
#include <codecvt>
#include <fstream>
#include <sstream>
#include <tlhelp32.h>

void ReportIssue(LPCWSTR message);
std::wstring convertStringToWString(const std::string& s);
DWORD GetProcessIdByName(const wchar_t* processName);
HANDLE getMinecraftWindowHandle();
void InjectDLL(HANDLE minecraftHandle, const std::string& path);