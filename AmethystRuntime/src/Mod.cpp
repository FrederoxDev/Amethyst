#include "Mod.h"

Mod::Mod(const char* mod_name) {
	this->mod_name = mod_name;
	fs::path dll_path = GetTempDll();

	// Loads the mod in a temporary directory so that the original DLL can still be built to
	hModule = LoadLibrary(dll_path.string().c_str());
	if (hModule == NULL) {
		DWORD error = GetLastError();

		if (error == 0x5) {
			Log::Error("[{}] '{}' does not have the required privileges!\n", mod_name, dll_path.string());
			throw std::exception();
		}

		else if (error == 0x7e) {
			Log::Error("[{}] Failed to find '{}'\n", mod_name, dll_path.string());
			throw std::exception();
		}

		else {
			Log::Error("[{}] Failed to load {}.dll, error code: 0x{:x}\n", mod_name, mod_name, error);
			throw std::exception();
		}
	}

	return;
}

FARPROC Mod::GetFunction(const char* func_name) {
	return GetProcAddress(hModule, func_name);
}

void Mod::Free() {
	FreeLibrary(hModule);
}

fs::path Mod::GetTempDll() {
	// Ensure temp directory exists
	fs::path temp_dir = GetAmethystFolder() + "temp/" + mod_name + "/";
	if (!fs::exists(temp_dir)) fs::create_directories(temp_dir);

	fs::path original_dll = GetAmethystFolder() + "mods/" + mod_name + "/" + mod_name + ".dll";
	if (!fs::exists(original_dll)) {
		Log::Error("[{}] Could not find {}.dll\n", mod_name, mod_name);
		throw std::exception();
	}

	fs::path temp_dll = temp_dir.string() + mod_name + ".dll";

	try {
		fs::copy_file(original_dll, temp_dll, fs::copy_options::overwrite_existing);
	}
	catch (const std::filesystem::filesystem_error& e) {
		Log::Error("[AmethystRuntime] {} (Error code: {})\n", e.what(), e.code().value());
		throw std::exception();
	}

	return temp_dll;
}