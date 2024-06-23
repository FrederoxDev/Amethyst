; Written by rydev, in-hand

section .text
extern FillingContainer_vtable

global ?serverInitItemStackIds@FillingContainer@@UEAAXHHV?$function@$$A6AXHAEBVItemStack@@@Z@std@@@Z
?serverInitItemStackIds@FillingContainer@@UEAAXHHV?$function@$$A6AXHAEBVItemStack@@@Z@std@@@Z:
    mov rax, [rel FillingContainer_vtable]
    jmp [rax + 16]

global ?setItemWithForceBalance@FillingContainer@@UEAAXHAEBVItemStack@@_N@Z
?setItemWithForceBalance@FillingContainer@@UEAAXHAEBVItemStack@@_N@Z:
    mov rax, [rel FillingContainer_vtable]
    jmp [rax + 104]
    
global ?removeItem@FillingContainer@@UEAAXHH@Z
?removeItem@FillingContainer@@UEAAXHH@Z:
    mov rax, [rel FillingContainer_vtable]
    jmp [rax + 112]
    
global ?add@FillingContainer@@UEAAXAEAVItemStack@@@Z
?add@FillingContainer@@UEAAXAEAVItemStack@@@Z:
    mov rax, [rel FillingContainer_vtable]
    jmp [rax + 328]

global ?canAdd@FillingContainer@@UEAA_NAEBVItemStack@@@Z
?canAdd@FillingContainer@@UEAA_NAEBVItemStack@@@Z:
    mov rax, [rel FillingContainer_vtable]
    jmp [rax + 336]

global ?clearSlot@FillingContainer@@UEAAXH@Z
?clearSlot@FillingContainer@@UEAAXH@Z:
    mov rax, [rel FillingContainer_vtable]
    jmp [rax + 344]

global ?clearInventory@FillingContainer@@UEAAXH@Z
?clearInventory@FillingContainer@@UEAAXH@Z:
    mov rax, [rel FillingContainer_vtable]
    jmp [rax + 352]

global ?load@FillingContainer@@UEAAXAEBVListTag@@AEBVSemVersion@@AEAVLevel@@@Z
?load@FillingContainer@@UEAAXAEBVListTag@@AEBVSemVersion@@AEAVLevel@@@Z:
    mov rax, [rel FillingContainer_vtable]
    jmp [rax + 360]