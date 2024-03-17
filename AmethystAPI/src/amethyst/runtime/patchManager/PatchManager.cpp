#include "PatchManager.h"
#include "../../Log.h"
#include "../../Memory.h"
namespace Amethyst {
    // Returns false if the patch failed to apply
    bool PatchManager::ApplyPatch(PatchAddress address, uint8_t* patch, size_t size) {
        address = (void*)(GetMinecraftBaseAddress() + (uint64_t)address);
        DWORD oldProtection;
        if (!UnprotectMemory(address, size, &oldProtection)) {
            Log::Error("Failed to unprotect memory at address: 0x{0:x}", address);
			return false;
		}
        Patch ptch;
        auto it = this->m_Patches.find(address);
        if (it != this->m_Patches.end()) [[unlikely]] {
            if (memcmp(it->second.address, patch, size)) {
                Log::Warning("Patch already applied at address: 0x{0:x}", address);
                ptch.original = it->second.original;
            }
		}
        if (ptch.original.original == nullptr) {
			OriginalMemory original;
			uint8_t* originalMemory = (uint8_t*)malloc(size);
			memcpy(originalMemory, address, size);
			original.original = originalMemory;
            original.size = size;
			ptch.original = original;
        }
        ptch.address = address;
        memcpy(address, patch, size);
        this->m_Patches[address] = ptch;

        if (!ProtectMemory(address, size, oldProtection)) {
            Log::Error("Failed to protect memory at address: 0x{0:x}", address);
            return false;
        }
		return true;

    }

    void PatchManager::RemovePatch(PatchAddress address)
    {
        auto it = this->m_Patches.find(address);
		if (it != this->m_Patches.end()) {
			DWORD oldProtection;
			if (!UnprotectMemory(address, it->second.original.size, &oldProtection)) {
				Log::Error("Failed to unprotect memory at address: 0x{0:x}", address);
				return;
			}
			memcpy(address, it->second.original.original, it->second.original.size);
			if (!ProtectMemory(address, it->second.original.size, oldProtection)) {
				Log::Error("Failed to protect memory at address: 0x{0:x}", address);
				return;
			}
			free(it->second.original.original);
			this->m_Patches.erase(it);
		}

    }

    void PatchManager::RemoveAllPatches()
    {
		for (auto it = this->m_Patches.begin(); it != this->m_Patches.end(); it++) {
            RemovePatch(it->first);
		}
		this->m_Patches.clear();
    }

} // namespace Amethyst