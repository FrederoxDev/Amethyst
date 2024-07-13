#pragma once
#include <cstdint>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <vector>
namespace Amethyst {
	class PatchManager {
	public:		
		template<typename T>
        void ApplyPatch(uintptr_t address, T patch){
			return ApplyPatch(address, (uint8_t*)&patch, sizeof(T));
		}

        void ApplyPatch(uintptr_t address, uint8_t* patch, size_t size);
        ~PatchManager();

    private:

		struct OriginalMemory {
			uint8_t* original = nullptr;
			size_t size = 0;
		};

		struct Patch {
            uintptr_t address = 0x0;
            OriginalMemory original = {};
		};

		std::vector<Patch> mPatches;

		friend class AmethystRuntime;
	};
}