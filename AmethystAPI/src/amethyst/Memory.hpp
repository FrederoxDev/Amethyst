#pragma once
#include "amethyst-deps/Zydis.h"
#include "amethyst/Log.hpp"
#include <chrono>
#include <cstdint>
#include <psapi.h>
#include <string>
#include <vector>
#include <string_view>
#define WIN32_LEAN_AND_MEAN
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>

/*
Returns the position where Minecraft has been loaded into memory
*/
uintptr_t GetMinecraftBaseAddress();

/*
Returns the size of the game (in bytes) while loaded in memory
*/
unsigned long GetMinecraftSize();

/*
Offsets an address from the game binary, with the position the game has been loaded into memory at
*/
uintptr_t SlideAddress(uintptr_t offset);

/*
Finds an address of a function with its signature within the loaded game memory
*/
std::optional<uintptr_t> SigScanSafe(std::string_view signature);

/*
Finds an address of a function with its signature within the loaded game memory
*/
uintptr_t SigScan(std::string_view signature);

/**
 * Finds the offset of a pointer in a struct/class
 * returns SIZE_MAX if it fails
*/
size_t FindOffsetOfPointer(void* _base, void* _pointer, size_t maxSearchSize);

/**
 * Unprotects the memory region 
*/
void UnprotectMemory(uintptr_t address, size_t size, DWORD* oldProtection);

/**
 * Reprotects the memory region
*/
void ProtectMemory(uintptr_t address, size_t size, DWORD protectionData, DWORD* oldProtection = nullptr);

/*
 * Computes the effective target address for common RIP-relative instructions.
 *
 * Supported instruction patterns:
 *   - lea reg, [rip + disp32]
 *   - call rel32
 *   - jmp rel32
 *   - call [rip + disp32]
 *   - jmp [rip + disp32]
 *
 * For direct relative instructions (call/jmp rel32), the displacement is
 * sign-extended and added to the address *after* the instruction.
 *
 * For memory-indirect forms (call/jmp [rip + disp32]), the target address
 * is resolved by reading the pointer located at (rip + disp32 + sizeof(instr)).
 *
 * If the instruction does not match one of these cases, the input address
 * is returned unchanged.
 *
 * Parameters:
 *   address - Address of the instruction to decode.
 *
 * Returns:
 *   The resolved absolute target address if RIP-relative; otherwise, the input address.
 */
uintptr_t GetEffectiveAddress(uintptr_t address);

uintptr_t GetVtable(void* obj);
uintptr_t GetVtable(const void* obj);

/*
 * Compares two virtual tables and logs any differences
 * Be aware that if one of the virtual destructors of any functions are imported from the game there will always be a mismatch between them.
 */
void CompareVirtualTables(uintptr_t lhs, uintptr_t rhs, size_t maxFunctions);

/*
 * Compares two virtual tables and logs any differences
 * Be aware that if one of the virtual destructors of any functions are imported from the game there will always be a mismatch between them.
 */
template <typename ObjT>
void CompareVirtualTables(ObjT* lhs, uintptr_t rhs, size_t maxFunctions) {
    CompareVirtualTables(GetVtable(lhs), rhs, maxFunctions);
}

/*
 * Compares two virtual tables and logs any differences
 * Be aware that if one of the virtual destructors of any functions are imported from the game there will always be a mismatch between them.
 */
template <typename ObjT>
void CompareVirtualTables(uintptr_t lhs, ObjT* rhs, size_t maxFunctions)
{
    CompareVirtualTables(lhs, GetVtable(rhs), maxFunctions);
}

/*
 * Compares two virtual tables and logs any differences
 * Be aware that if one of the virtual destructors of any functions are imported from the game there will always be a mismatch between them.
 */
template <typename ObjT>
void CompareVirtualTables(ObjT* lhs, ObjT* rhs, size_t maxFunctions) {
    CompareVirtualTables(GetVtable(lhs), GetVtable(rhs), maxFunctions);
}

/*
 * Returns the virtual offset of a virtual function from a thunk
 */
template <auto T>
size_t GetVirtualFunctionOffset() {
    using FnType = decltype(T);
    union {
        FnType func;
        uintptr_t addr;
    } u;
    u.func = T;
    uintptr_t func = u.addr;
    ZydisDecoder decoder;
    ZydisDecoderInit(&decoder, ZYDIS_MACHINE_MODE_LONG_64, ZYDIS_STACK_WIDTH_64);

    ZydisDecodedInstruction instr;
    ZydisDecodedOperand operands[ZYDIS_MAX_OPERAND_COUNT];

    // Decode jmp rel32
    if (ZYAN_SUCCESS(ZydisDecoderDecodeFull(&decoder, reinterpret_cast<const void*>(func), 16, &instr, operands))) {
        if (instr.mnemonic == ZYDIS_MNEMONIC_JMP && instr.operand_count == 2 && operands[0].type == ZYDIS_OPERAND_TYPE_IMMEDIATE) {
            func += instr.length + operands[0].imm.value.s;
        }
    }
    else {
        Log::Error("[AmethystRuntime] GetVirtualFunctionOffset: Failed to decode instruction at {:x}", func);
        return 0;
    }

    
    if (ZYAN_SUCCESS(ZydisDecoderDecodeFull(&decoder, reinterpret_cast<const void*>(func), 16, &instr, operands))) {
        // Decode first instruction (mov rax, ...)
        if (instr.mnemonic == ZYDIS_MNEMONIC_MOV) {
            func += instr.length;
            if (!ZYAN_SUCCESS(ZydisDecoderDecodeFull(&decoder, reinterpret_cast<const void*>(func), 16, &instr, operands))) {
                Log::Error("[AmethystRuntime] GetVirtualFunctionOffset: Failed to decode instruction at {:x}", func);
                return 0;
            }
        }
        
        // Decode second instruction (jmp [rax+disp])
        if (instr.mnemonic != ZYDIS_MNEMONIC_JMP || operands[0].type != ZYDIS_OPERAND_TYPE_MEMORY) {
            Log::Error("[AmethystRuntime] GetVirtualFunctionOffset: Expected jmp [rax+disp] instruction.");
            return 0;
        }

        const auto& mem = operands[0].mem;
        if (mem.base != ZYDIS_REGISTER_RAX) {
            Log::Error("[AmethystRuntime] GetVirtualFunctionOffset: Expected base register to be RAX.");
            return 0;
        }

        // disp.value holds either disp8 or disp32 already sign-extended
        return static_cast<size_t>(mem.disp.value);
    }
    else {
        Log::Error("[AmethystRuntime] GetVirtualFunctionOffset: Failed to decode instruction at {:x}", func);
    }
    return 0;
}
