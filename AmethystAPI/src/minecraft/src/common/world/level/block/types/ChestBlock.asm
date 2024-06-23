; Written by rydev, in-hand

section .text
extern ChestBlock_vtable
extern ChestBlock_ctor

global ??0ChestBlock@@QEAA@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@FW4ChestType@0@W4MaterialType@@@Z
??0ChestBlock@@QEAA@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@FW4ChestType@0@W4MaterialType@@@Z:
    mov rax, [rel ChestBlock_ctor]
    jmp rax
    
global ?dispense@ChestBlock@@UEBA_NAEAVBlockSource@@AEAVContainer@@HAEBVVec3@@E@Z
?dispense@ChestBlock@@UEBA_NAEAVBlockSource@@AEAVContainer@@HAEBVVec3@@E@Z:
	mov rax, [rel ChestBlock_vtable]
	jmp [rax + 512]

global ?onMove@ChestBlock@@UEBAXAEAVBlockSource@@AEBVBlockPos@@1@Z
?onMove@ChestBlock@@UEBAXAEAVBlockSource@@AEBVBlockPos@@1@Z:
	mov rax, [rel ChestBlock_vtable]
	jmp [rax + 536]
	
global ?setupRedstoneComponent@ChestBlock@@UEBAXAEAVBlockSource@@AEBVBlockPos@@@Z
?setupRedstoneComponent@ChestBlock@@UEBAXAEAVBlockSource@@AEBVBlockPos@@@Z:
	mov rax, [rel ChestBlock_vtable]
	jmp [rax + 576]
	
global ?getSecondPart@ChestBlock@@UEBA_NAEBVIConstBlockSource@@AEBVBlockPos@@AEAV3@@Z
?getSecondPart@ChestBlock@@UEBA_NAEBVIConstBlockSource@@AEBVBlockPos@@AEAV3@@Z:
	mov rax, [rel ChestBlock_vtable]
	jmp [rax + 752]
	
global ?getComparatorSignal@ChestBlock@@UEBAHAEAVBlockSource@@AEBVBlockPos@@AEBVBlock@@E@Z
?getComparatorSignal@ChestBlock@@UEBAHAEAVBlockSource@@AEBVBlockPos@@AEBVBlock@@E@Z:
	mov rax, [rel ChestBlock_vtable]
	jmp [rax + 896]
	
global ?getMappedFace@ChestBlock@@UEBAEEAEBVBlock@@@Z
?getMappedFace@ChestBlock@@UEBAEEAEBVBlock@@@Z:
	mov rax, [rel ChestBlock_vtable]
	jmp [rax + 1056]
	
global ?init@ChestBlock@@UEAAAEAV1@XZ
?init@ChestBlock@@UEAAAEAV1@XZ:
	mov rax, [rel ChestBlock_vtable]
	jmp [rax + 1088]
	
global ?onRemove@ChestBlock@@MEBAXAEAVBlockSource@@AEBVBlockPos@@@Z
?onRemove@ChestBlock@@MEBAXAEAVBlockSource@@AEBVBlockPos@@@Z:
	mov rax, [rel ChestBlock_vtable]
	jmp [rax + 1144]
	
global ?onPlace@ChestBlock@@MEBAXAEAVBlockSource@@AEBVBlockPos@@@Z
?onPlace@ChestBlock@@MEBAXAEAVBlockSource@@AEBVBlockPos@@@Z:
	mov rax, [rel ChestBlock_vtable]
	jmp [rax + 1168]
	
global ?use@ChestBlock@@MEBA_NAEAVPlayer@@AEBVBlockPos@@E@Z
?use@ChestBlock@@MEBA_NAEAVPlayer@@AEBVBlockPos@@E@Z:
	mov rax, [rel ChestBlock_vtable]
	jmp [rax + 1208]