section .text
extern Packet_vtable

global ?checkSize@Packet@@UEBA?AV?$Result@XVerror_code@std@@@Bedrock@@_K_N@Z
?checkSize@Packet@@UEBA?AV?$Result@XVerror_code@std@@@Bedrock@@_K_N@Z:
    mov rax, [rel Packet_vtable]
	jmp [rax + 24]

global ?read@Packet@@UEAA?AV?$Result@XVerror_code@std@@@Bedrock@@AEAVReadOnlyBinaryStream@@@Z
?read@Packet@@UEAA?AV?$Result@XVerror_code@std@@@Bedrock@@AEAVReadOnlyBinaryStream@@@Z:
    mov rax, [rel Packet_vtable]
	jmp [rax + 40]