#pragma once
#include "amethyst-deps/Zydis.h"
#include "amethyst/Log.hpp"
#include <chrono>
#include <cstdint>
#include <optional>
#include <psapi.h>
#include <string>
#include <vector>
#include <string_view>
#include <Windows.h>

/*
Identifies one exact link of the game binary, taken from the CodeView record the linker embeds in the executable
*/
struct MinecraftBuildId {
    std::string Guid;
    uint32_t Age;
};

/*
Returns the position where Minecraft has been loaded into memory
*/
uintptr_t GetMinecraftBaseAddress();

/*
Returns the size of the game (in bytes) while loaded in memory
*/
unsigned long GetMinecraftSize();

/*
Returns the build identity of the loaded game, or nothing when the executable carries no CodeView record.

Version strings do not identify a build: two different links can share one version, and a lower version number
can be the newer link. The CodeView GUID changes with every link, so it is what hardcoded addresses are valid against.
*/
std::optional<MinecraftBuildId> GetMinecraftBuildId();

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
 * Returns the virtual offset of a virtual function from a thunk.
 *
 * MSVC emits virtual-PMF thunks in several shapes depending on inheritance:
 *   1) MSVC single inheritance:   mov rax,[rcx]; jmp [rax+disp]
 *   2) MSVC adjustor:             add rcx,N; mov rax,[rcx]; jmp [rax+disp]
 *                              or sub rcx,N; ...
 *                              or lea rcx,[rcx+N]; ...
 *   3) Clang single inheritance:  mov rax,[rcx]; mov rax,[rax+disp]; jmp rax
 *   4) Clang adjustor:            add/sub/lea rcx,N; mov rax,[rcx]; mov rax,[rax+disp]; jmp rax
 *   5) Wrapped:                   jmp rel32 -> any of the above
 *
 * Any of the above may be preceded by `endbr64` (Intel CET branch-tracking)
 * when the consumer was built with `-fcf-protection=branch` or `full` (clang's
 * default on recent versions). We skip endbr64 silently.
 *
 * Walk forward past any `add/sub/lea rcx`, the vtable load `mov rax,[rcx(+X)]`,
 * an optional clang-style slot load `mov rax,[rax+disp]` (remembering disp), and
 * finally one of:
 *   - `jmp [rax+disp]`  (MSVC) → return disp from the operand
 *   - `jmp rax`         (clang) → return the disp from the prior slot-load mov
 * Anything else is unexpected.
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

    // Optional leading jmp rel32 (wrapper).
    if (!ZYAN_SUCCESS(ZydisDecoderDecodeFull(&decoder, reinterpret_cast<const void*>(func), 16, &instr, operands))) {
        Log::Error("[AmethystRuntime] GetVirtualFunctionOffset: Failed to decode instruction at {:x}", func);
        return 0;
    }
    if (instr.mnemonic == ZYDIS_MNEMONIC_JMP && operands[0].type == ZYDIS_OPERAND_TYPE_IMMEDIATE) {
        func += instr.length + operands[0].imm.value.s;
    }

    // Optional CET branch-tracking prologue (clang with -fcf-protection=branch|full).
    if (!ZYAN_SUCCESS(ZydisDecoderDecodeFull(&decoder, reinterpret_cast<const void*>(func), 16, &instr, operands))) {
        Log::Error("[AmethystRuntime] GetVirtualFunctionOffset: Failed to decode instruction at {:x}", func);
        return 0;
    }
    if (instr.mnemonic == ZYDIS_MNEMONIC_ENDBR64 || instr.mnemonic == ZYDIS_MNEMONIC_ENDBR32) {
        func += instr.length;
    }

    // Slot offset captured by a clang-style `mov rax, [rax + disp]` slot load,
    // used by the trailing `jmp rax` to return the right value.
    size_t pendingSlot = 0;
    bool haveSlotLoad = false;

    // Walk through optional adjustor + load instructions, stopping at the dispatching jmp.
    for (int i = 0; i < 8; ++i) {
        if (!ZYAN_SUCCESS(ZydisDecoderDecodeFull(&decoder, reinterpret_cast<const void*>(func), 16, &instr, operands))) {
            Log::Error("[AmethystRuntime] GetVirtualFunctionOffset: Failed to decode instruction at {:x}", func);
            return 0;
        }

        // MSVC final: jmp [rax+disp] — extract slot offset from the memory operand.
        if (instr.mnemonic == ZYDIS_MNEMONIC_JMP
            && operands[0].type == ZYDIS_OPERAND_TYPE_MEMORY
            && operands[0].mem.base == ZYDIS_REGISTER_RAX) {
            return static_cast<size_t>(operands[0].mem.disp.value);
        }

        // Clang final: jmp rax — slot offset was captured by the preceding mov.
        if (instr.mnemonic == ZYDIS_MNEMONIC_JMP
            && operands[0].type == ZYDIS_OPERAND_TYPE_REGISTER
            && operands[0].reg.value == ZYDIS_REGISTER_RAX
            && haveSlotLoad) {
            return pendingSlot;
        }

        // Permitted prologue: this-pointer adjustors and the vtable load.
        const bool isAdjustor =
            (instr.mnemonic == ZYDIS_MNEMONIC_ADD || instr.mnemonic == ZYDIS_MNEMONIC_SUB || instr.mnemonic == ZYDIS_MNEMONIC_LEA)
            && operands[0].type == ZYDIS_OPERAND_TYPE_REGISTER
            && operands[0].reg.value == ZYDIS_REGISTER_RCX;
        const bool isVtableLoad =
            instr.mnemonic == ZYDIS_MNEMONIC_MOV
            && operands[0].type == ZYDIS_OPERAND_TYPE_REGISTER
            && operands[0].reg.value == ZYDIS_REGISTER_RAX
            && operands[1].type == ZYDIS_OPERAND_TYPE_MEMORY
            && operands[1].mem.base == ZYDIS_REGISTER_RCX;
        // Clang slot load: `mov rax, [rax + disp]` — remember disp for the
        // upcoming `jmp rax`.
        const bool isSlotLoad =
            instr.mnemonic == ZYDIS_MNEMONIC_MOV
            && operands[0].type == ZYDIS_OPERAND_TYPE_REGISTER
            && operands[0].reg.value == ZYDIS_REGISTER_RAX
            && operands[1].type == ZYDIS_OPERAND_TYPE_MEMORY
            && operands[1].mem.base == ZYDIS_REGISTER_RAX;
        if (isSlotLoad) {
            pendingSlot = static_cast<size_t>(operands[1].mem.disp.value);
            haveSlotLoad = true;
        }

        if (!isAdjustor && !isVtableLoad && !isSlotLoad) {
            Log::Error("[AmethystRuntime] GetVirtualFunctionOffset: Unexpected instruction at {:x} (mnemonic={})",
                func, static_cast<int>(instr.mnemonic));
            return 0;
        }

        func += instr.length;
    }

    Log::Error("[AmethystRuntime] GetVirtualFunctionOffset: Walked too many prologue instructions without finding dispatch jmp");
    return 0;
}
