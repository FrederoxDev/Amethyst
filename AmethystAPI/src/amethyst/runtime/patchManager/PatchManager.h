#pragma once
#include <cstdint>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <unordered_map>

using PatchAddress = void*;

namespace Amethyst {
	class PatchManager {
	public:
		PatchManager() {}
        ~PatchManager() { RemoveAllPatches(); }
		
		template<typename T>
        bool ApplyPatch(PatchAddress address, T patch){
			return ApplyPatch(address, (uint8_t*)&patch, sizeof(T));
		}
        bool ApplyPatch(PatchAddress address, uint8_t* patch, size_t size);

		void RemovePatch(PatchAddress address);

		void RemoveAllPatches();
	private:
         bool UnprotectMemory(PatchAddress address, size_t size, DWORD* oldProtection);
         bool ProtectMemory(PatchAddress address, size_t size, DWORD oldProtection);

    private:
		struct OriginalMemory {
			uint8_t* original = nullptr;
			size_t size = 0;
		};
		struct Patch {
            PatchAddress address = 0x0;
            OriginalMemory original = {};
		};
		std::unordered_map<PatchAddress, Patch> m_Patches; // Tbh a vector would be faster because i dont expect a lot of patches


	};
}