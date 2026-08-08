#include "amethyst/Memory.hpp"
#include <libhat/Scanner.hpp>
#include <cstring>
#include <format>
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

namespace {
#pragma pack(push, 1)
struct CodeViewRSDS {
    char Signature[4];
    GUID Guid;
    uint32_t Age;
};
#pragma pack(pop)

std::string FormatGuid(const GUID& guid)
{
    return std::format("{:08X}-{:04X}-{:04X}-{:02X}{:02X}-{:02X}{:02X}{:02X}{:02X}{:02X}{:02X}",
        guid.Data1, guid.Data2, guid.Data3,
        guid.Data4[0], guid.Data4[1],
        guid.Data4[2], guid.Data4[3], guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);
}

std::optional<MinecraftBuildId> ReadBuildId(uintptr_t base)
{
    auto* dosHeader = reinterpret_cast<IMAGE_DOS_HEADER*>(base);
    if (dosHeader->e_magic != IMAGE_DOS_SIGNATURE) return std::nullopt;

    auto* ntHeaders = reinterpret_cast<IMAGE_NT_HEADERS64*>(base + dosHeader->e_lfanew);
    if (ntHeaders->Signature != IMAGE_NT_SIGNATURE) return std::nullopt;

    const IMAGE_DATA_DIRECTORY& directory = ntHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_DEBUG];
    if (directory.VirtualAddress == 0) return std::nullopt;

    auto* entries = reinterpret_cast<IMAGE_DEBUG_DIRECTORY*>(base + directory.VirtualAddress);
    size_t entryCount = directory.Size / sizeof(IMAGE_DEBUG_DIRECTORY);

    for (size_t i = 0; i < entryCount; i++) {
        const IMAGE_DEBUG_DIRECTORY& entry = entries[i];
        if (entry.Type != IMAGE_DEBUG_TYPE_CODEVIEW) continue;
        if (entry.AddressOfRawData == 0 || entry.SizeOfData < sizeof(CodeViewRSDS)) continue;

        // The image is mapped, so the record sits at its RVA. PointerToRawData is a file offset and would read unrelated bytes here.
        auto* record = reinterpret_cast<const CodeViewRSDS*>(base + entry.AddressOfRawData);
        if (memcmp(record->Signature, "RSDS", sizeof(record->Signature)) != 0) continue;

        return MinecraftBuildId{ FormatGuid(record->Guid), record->Age };
    }

    return std::nullopt;
}
} // namespace

std::optional<MinecraftBuildId> GetMinecraftBuildId()
{
    static const std::optional<MinecraftBuildId> buildId = ReadBuildId(GetMinecraftBaseAddress());
    return buildId;
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

uintptr_t GetVtable(const void* obj) {
	return *reinterpret_cast<uintptr_t const*>(obj);
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
