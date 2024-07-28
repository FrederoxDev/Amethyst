#pragma once
#include <cstdint>
#include <WinBase.h>
#include <amethyst-deps/Zydis.h>
#include <amethyst/Log.hpp>
#include <amethyst/Memory.hpp>

static void LogAssemblyOfExceptionCause(uintptr_t address) 
{
    ZydisDecoder decoder;
    ZydisDecoderInit(&decoder, ZYDIS_MACHINE_MODE_LONG_64, ZYDIS_STACK_WIDTH_64);

    ZydisFormatter formatter;
    ZydisFormatterInit(&formatter, ZYDIS_FORMATTER_STYLE_INTEL);

    // Try and read some instructions at the address of the crash
    const uint64_t dataSize = 16;
    if (IsBadReadPtr((void*)address, dataSize)) {
        Log::Warning("Failed to print assembly of crash, bad ptr to exception cause!");
        return;
    }

    // Copy the bytes out to pass to zydis
    uint8_t* data = (uint8_t*)address;

    // Attempt to decode the bytes with zydis
    ZyanUSize offset = 0;
    ZydisDecodedInstruction instruction;
    ZydisDecodedOperand operands[ZYDIS_MAX_OPERAND_COUNT];

    uint64_t idaOffset = address - GetMinecraftBaseAddress() + 0x140000000;
    bool isLineWithError = true;

    Log::Error("Disassembly:");

    while (ZYAN_SUCCESS(ZydisDecoderDecodeFull(&decoder, data + offset, dataSize - offset, &instruction, operands))) {
        // Format & print the binary instruction structure to human-readable format
        char buffer[256];
        ZydisFormatterFormatInstruction(
            &formatter, &instruction, operands, instruction.operand_count_visible, buffer, sizeof(buffer), ZYDIS_RUNTIME_ADDRESS_NONE, ZYAN_NULL
        );

        Log::Error("{:16X} {:s}", idaOffset + offset, buffer, strlen(buffer));

        if (isLineWithError) {
            std::string whitespace(16, ' ');
            std::string instruction(strlen(buffer), '^');

            Log::Error("{} {}", whitespace, instruction);
            isLineWithError = false;
        }

        offset += instruction.length; 
    }
}