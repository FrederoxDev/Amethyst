#include "PatchManager.h"
#include "../../Log.h"
#include "../../Memory.h"
namespace Amethyst {
    // Returns false if the patch failed to apply
    bool PatchManager::ApplyPatch(uintptr_t address, uint8_t* patch, size_t size){
        DWORD oldProtection;
        if (!UnprotectMemory(address, size, &oldProtection)) {
            Assert("Failed to unprotect memory at address: 0x{0:x}", address);
			return false;
		}

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
        if (!ProtectMemory(address, size, oldProtection)) {
            Assert("Failed to protect memory at address: 0x{0:x}", address);
            return false;
        }
		return true;

    }

    void PatchManager::RemovePatch(uintptr_t address) {
    }

    void PatchManager::RemoveAllPatches()
    {
        uintptr_t address = -1;
		for (auto it = this->mPatches.rbegin(); it != this->mPatches.rend(); it++) {
			address = it->address;
			DWORD oldProtection;
			if (!UnprotectMemory(address, it->original.size, &oldProtection)) {
				Assert("Failed to unprotect memory at address: 0x{0:x}", address);
			}
			memcpy(reinterpret_cast<void*>(address), it->original.original, it->original.size);
			if (!ProtectMemory(address, it->original.size, oldProtection)) {
				Assert("Failed to protect memory at address: 0x{0:x}", address);
			}
			free(it->original.original);
		}
		this->mPatches.clear();
    }

} // namespace Amethyst