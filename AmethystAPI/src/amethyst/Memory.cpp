#include "amethyst/Memory.hpp"
#include <libhat/Scanner.hpp>
#include <mutex>
#include <thread>
#include <optional>
#include <amethyst/runtime/ModContext.hpp>

uintptr_t GetMinecraftBaseAddress()
{
	static uintptr_t mc = Amethyst::GetPlatform().GetMinecraftBaseAddress();
    return mc;
}

unsigned long GetMinecraftSize()
{
	static size_t mc = Amethyst::GetPlatform().GetMinecraftSize();
	return mc;
}

uintptr_t SlideAddress(uintptr_t offset)
{
    return GetMinecraftBaseAddress() + offset;
}

std::optional<uintptr_t> SigScanSafe(std::string_view signature)
{
    const auto parsed = hat::parse_signature(signature);
    Assert(parsed.has_value(), "Invalid signature! {:s}", signature);

    const auto begin = reinterpret_cast<std::byte*>(GetMinecraftBaseAddress());
    const auto end = begin + GetMinecraftSize();
    const auto result = hat::find_pattern(begin, end, parsed.value());

    if (!result.has_result()) return std::nullopt;
    return reinterpret_cast<uintptr_t>(result.get());
}

uintptr_t SigScan(std::string_view signature) {
    auto result = SigScanSafe(signature);
    Assert(result.has_value(), "Failed to find signature \"{:s}\"", signature);

    return result.value();
}

size_t FindOffsetOfPointer(void* _base, void* _pointer, size_t maxSearchSize)
{
    uintptr_t base = reinterpret_cast<uintptr_t>(_base);
    uintptr_t pointer = reinterpret_cast<uintptr_t>(_pointer);

    for (size_t offset = 0; offset < maxSearchSize; offset++) {
        uintptr_t ptrAtOffset = *reinterpret_cast<uintptr_t*>(base + offset);
        if (ptrAtOffset == pointer) return offset;
    }

    return SIZE_MAX;
}

void UnprotectMemory(uintptr_t address, size_t size, DWORD* oldProtection)
{
    return ProtectMemory(address, size, PAGE_EXECUTE_READWRITE, oldProtection);
}

void ProtectMemory(uintptr_t address, size_t size, DWORD protectionData, DWORD* oldProtection)
{
    DWORD oldProtect;
    if (oldProtection != nullptr) oldProtect = *oldProtection;
	else oldProtect = DWORD();

    Assert(VirtualProtect(reinterpret_cast<void*>(address), size, protectionData, &oldProtect), "Failed to reprotect memory at 0x{:X}! Error: {}", address, GetLastError());

	if (oldProtection != nullptr) *oldProtection = oldProtect;
}

// Since those functions are very workaroundy and not performance critical, disable optimizations to make debugging easier.
#pragma optimize("", off)
uintptr_t GetEffectiveAddress(uintptr_t address) {
	ZydisDecoder decoder;
	ZydisDecoderInit(&decoder, ZYDIS_MACHINE_MODE_LONG_64, ZYDIS_STACK_WIDTH_64);

	ZydisDecodedInstruction instr;
	ZydisDecodedOperand operands[ZYDIS_MAX_OPERAND_COUNT];
	if (ZYAN_SUCCESS(ZydisDecoderDecodeFull(&decoder, reinterpret_cast<const void*>(address), ZYDIS_MAX_INSTRUCTION_LENGTH, &instr, operands))) {
		// lea ...
		if (instr.mnemonic == ZYDIS_MNEMONIC_LEA) {
			// ... reg, [rip + disp32]
			if (instr.operand_count_visible == 2 &&
				operands[0].type == ZYDIS_OPERAND_TYPE_REGISTER &&
				operands[1].type == ZYDIS_OPERAND_TYPE_MEMORY &&
				operands[1].mem.base == ZYDIS_REGISTER_RIP &&
				operands[1].mem.disp.has_displacement &&
				operands[1].mem.index == ZYDIS_REGISTER_NONE)
				return address + instr.length + operands[1].mem.disp.value;
		}

		// call|jmp ...
		if (instr.mnemonic == ZYDIS_MNEMONIC_CALL || instr.mnemonic == ZYDIS_MNEMONIC_JMP) {
			// ... rel32
			if (instr.operand_count_visible == 1 && 
				operands[0].type == ZYDIS_OPERAND_TYPE_IMMEDIATE)
				return address + instr.length + operands[0].imm.value.s;

			// ... [rip + disp32]
			if (instr.operand_count_visible == 1 &&
				operands[0].type == ZYDIS_OPERAND_TYPE_MEMORY &&
				operands[0].mem.base == ZYDIS_REGISTER_RIP &&
				operands[0].mem.disp.has_displacement &&
				operands[0].mem.index == ZYDIS_REGISTER_NONE) {
				uintptr_t ptr = address + instr.length + operands[0].mem.disp.value;
				return *reinterpret_cast<uintptr_t*>(ptr);
			}
		}
	}

	return address;
}

uintptr_t GetVtable(void* obj)
{
    return (uintptr_t)*reinterpret_cast<uintptr_t**>(obj);
}

void CompareVirtualTables(uintptr_t lhs, uintptr_t rhs, size_t maxFunctions)
{
    Log::Info("Comparing virtual tables {:X} and {:X}", lhs, rhs);
    auto lhsArray = reinterpret_cast<uintptr_t*>(lhs);
    auto rhsArray = reinterpret_cast<uintptr_t*>(rhs);

    auto resolveJmp = [](uintptr_t addr) -> uintptr_t {
        unsigned char* bytes = reinterpret_cast<unsigned char*>(addr);
        if (bytes[0] == 0xFF && bytes[1] == 0x25) {
            int32_t ripOffset = *reinterpret_cast<int32_t*>(bytes + 2);
            return *reinterpret_cast<uintptr_t*>(addr + 6 + ripOffset);
        }
        return addr;
    };

    for (size_t i = 0; i < maxFunctions; i++) {
        uintptr_t lhsFunc = resolveJmp(lhsArray[i]) - GetMinecraftBaseAddress();
        uintptr_t rhsFunc = resolveJmp(rhsArray[i]) - GetMinecraftBaseAddress();
        if (lhsFunc != rhsFunc) {
            Log::Warning("Virtual table mismatch at index {}: {:X} != {:X}", i, lhsFunc, rhsFunc);
        }
    }
}
#pragma optimize("", on)