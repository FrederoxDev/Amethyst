; Written by rydev, in-hand

section .text
extern RandomizableBlockActorContainerBase_vtable

global ?load@RandomizableBlockActorContainerBase@@UEAAXAEAVLevel@@AEBVCompoundTag@@AEAVDataLoadHelper@@@Z
?load@RandomizableBlockActorContainerBase@@UEAAXAEAVLevel@@AEBVCompoundTag@@AEAVDataLoadHelper@@@Z:
    mov rax, [rel RandomizableBlockActorContainerBase_vtable]
    jmp [rax + 8]
    
global ?save@RandomizableBlockActorContainerBase@@UEBA_NAEAVCompoundTag@@@Z
?save@RandomizableBlockActorContainerBase@@UEBA_NAEAVCompoundTag@@@Z:
    mov rax, [rel RandomizableBlockActorContainerBase_vtable]
    jmp [rax + 16]
    
global ?eraseLootTable@RandomizableBlockActorContainerBase@@UEAAXXZ
?eraseLootTable@RandomizableBlockActorContainerBase@@UEAAXXZ:
    mov rax, [rel RandomizableBlockActorContainerBase_vtable]
    jmp [rax + 272]