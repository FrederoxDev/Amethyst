#include "PatchManager.hpp"
#include "amethyst/Log.hpp"
#include "amethyst/Memory.hpp"

namespace Amethyst {
    // Returns false if the patch failed to apply
    void PatchManager::ApplyPatch(uintptr_t address, uint8_t* patch, size_t size){
        DWORD oldProtection;
        UnprotectMemory(address, size, &oldProtection);

        uint64_t boundsLow = address;
        uint64_t boundsHigh = address + size;
        for (auto& establishedPatch : this->mPatches) {
			if (establishedPatch.address == address) {
                Log::Warning("Patch already exists at address: 0x{0:x}", address);
			}
            uint64_t establishedBoundsLow = establishedPatch.address;
            uint64_t establishedBoundsHigh = establishedPatch.address + establishedPatch.original.size;
            if (boundsLow >= establishedBoundsLow && boundsLow <= establishedBoundsHigh
                || boundsHigh >= establishedBoundsLow && boundsHigh <= establishedBoundsHigh) {
                Log::Warning("Patch at address: 0x{0:x} overlaps with existing patch at address: 0x{1:x}", address, establishedPatch.address);
			}
		}
        Patch ptch;
		OriginalMemory original;
		uint8_t* originalMemory = (uint8_t*)malloc(size);
        if (!originalMemory) 
			Assert("Failed to allocate memory for original bytes at address: 0x{0:x}", address);
        memcpy(originalMemory, reinterpret_cast<void*>(address), size);
		original.original = originalMemory;
        original.size = size;
		ptch.original = original;
        ptch.address = address;
        memcpy(reinterpret_cast<void*>(address), patch, size);
        this->mPatches.emplace_back(ptch);
        ProtectMemory(address, size, oldProtection);
        
    }

    void PatchManager::RemovePatch(uintptr_t address) {
    }

    void PatchManager::RemoveAllPatches()
    {
		for (auto it = this->mPatches.rbegin(); it != this->mPatches.rend(); it++) {
            uintptr_t address = it->address;
			DWORD oldProtection;
            UnprotectMemory(address, it->original.size, &oldProtection);
			memcpy(reinterpret_cast<void*>(address), it->original.original, it->original.size);
            ProtectMemory(address, it->original.size, oldProtection);
			free(it->original.original);
		}
		this->mPatches.clear();
    }

} // namespace Amethyst