; Written by rydev, in-hand

section .text
extern Container_ctor1
extern Container_ctor2
extern Container_vtable

global ??0Container@@QEAA@W4ContainerType@@@Z
??0Container@@QEAA@W4ContainerType@@@Z:
    mov rax, [rel Container_ctor1]
    jmp rax
    
global ??0Container@@QEAA@W4ContainerType@@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@_N@Z
??0Container@@QEAA@W4ContainerType@@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@_N@Z:
    mov rax, [rel Container_ctor2]
    jmp rax

global ??1Container@@UEAA@XZ
??1Container@@UEAA@XZ:
    mov rax, [rel Container_vtable]
    jmp [rax + 0]
    
global ?addContentChangeListener@Container@@UEAAXPEAVContainerContentChangeListener@@@Z
?addContentChangeListener@Container@@UEAAXPEAVContainerContentChangeListener@@@Z:
    mov rax, [rel Container_vtable]
    jmp [rax + 24]
    
global ?removeContentChangeListener@Container@@UEAAXPEAVContainerContentChangeListener@@@Z
?removeContentChangeListener@Container@@UEAAXPEAVContainerContentChangeListener@@@Z:
    mov rax, [rel Container_vtable]
    jmp [rax + 32]
    
global ?addRemovedListener@Container@@UEAAXPEAVContainerRemovedListener@@@Z
?addRemovedListener@Container@@UEAAXPEAVContainerRemovedListener@@@Z:
    mov rax, [rel Container_vtable]
    jmp [rax + 40]
    
global ?removeRemovedListener@Container@@UEAAXPEAVContainerRemovedListener@@@Z
?removeRemovedListener@Container@@UEAAXPEAVContainerRemovedListener@@@Z:
    mov rax, [rel Container_vtable]
    jmp [rax + 48]
    
global ?hasRoomForItem@Container@@UEAA_NAEBVItemStack@@@Z
?hasRoomForItem@Container@@UEAA_NAEBVItemStack@@@Z:
    mov rax, [rel Container_vtable]
    jmp [rax + 64]
    
global ?addItem@Container@@UEAAXAEAVItemStack@@@Z
?addItem@Container@@UEAAXAEAVItemStack@@@Z:
    mov rax, [rel Container_vtable]
    jmp [rax + 72]
    
global ?addItemWithForceBalance@Container@@UEAAXAEAVItemStack@@@Z
?addItemWithForceBalance@Container@@UEAAXAEAVItemStack@@@Z:
    mov rax, [rel Container_vtable]
    jmp [rax + 80]
    
global ?addItemToFirstEmptySlot@Container@@UEAA_NAEBVItemStack@@@Z
?addItemToFirstEmptySlot@Container@@UEAA_NAEBVItemStack@@@Z:
    mov rax, [rel Container_vtable]
    jmp [rax + 88]
    
global ?removeItem@Container@@UEAAXHH@Z
?removeItem@Container@@UEAAXHH@Z:
    mov rax, [rel Container_vtable]
    jmp [rax + 112]
    
global ?removeAllItems@Container@@UEAAXXZ
?removeAllItems@Container@@UEAAXXZ:
    mov rax, [rel Container_vtable]
    jmp [rax + 120]
    
global ?removeAllItemsWithForceBalance@Container@@UEAAXXZ
?removeAllItemsWithForceBalance@Container@@UEAAXXZ:
    mov rax, [rel Container_vtable]
    jmp [rax + 128]
    
global ?containerRemoved@Container@@UEAAXXZ
?containerRemoved@Container@@UEAAXXZ:
    mov rax, [rel Container_vtable]
    jmp [rax + 136]
    
global ?dropSlotContent@Container@@UEAAXAEAVBlockSource@@AEBVVec3@@_NH@Z
?dropSlotContent@Container@@UEAAXAEAVBlockSource@@AEBVVec3@@_NH@Z:
    mov rax, [rel Container_vtable]
    jmp [rax + 144]
    
global ?dropContents@Container@@UEAAXAEAVBlockSource@@AEBVVec3@@_N@Z
?dropContents@Container@@UEAAXAEAVBlockSource@@AEBVVec3@@_N@Z:
    mov rax, [rel Container_vtable]
    jmp [rax + 152]
    
global ?stopOpen@Container@@UEAAXAEAVPlayer@@@Z
?stopOpen@Container@@UEAAXAEAVPlayer@@@Z:
    mov rax, [rel Container_vtable]
    jmp [rax + 184]
    
global ?getSlotCopies@Container@@UEBA?AV?$vector@VItemStack@@V?$allocator@VItemStack@@@std@@@std@@XZ
?getSlotCopies@Container@@UEBA?AV?$vector@VItemStack@@V?$allocator@VItemStack@@@std@@@std@@XZ:
    mov rax, [rel Container_vtable]
    jmp [rax + 192]
    
global ?getSlots@Container@@UEBA?BV?$vector@PEBVItemStack@@V?$allocator@PEBVItemStack@@@std@@@std@@XZ
?getSlots@Container@@UEBA?BV?$vector@PEBVItemStack@@V?$allocator@PEBVItemStack@@@std@@@std@@XZ:
    mov rax, [rel Container_vtable]
    jmp [rax + 200]
    
global ?getEmptySlotsCount@Container@@UEBAHXZ
?getEmptySlotsCount@Container@@UEBAHXZ:
    mov rax, [rel Container_vtable]
    jmp [rax + 208]
    
global ?getItemCount@Container@@UEAAHAEBVItemStack@@@Z
?getItemCount@Container@@UEAAHAEBVItemStack@@@Z:
    mov rax, [rel Container_vtable]
    jmp [rax + 216]
    
global ?findFirstSlotForItem@Container@@UEBAHAEBVItemStack@@@Z
?findFirstSlotForItem@Container@@UEBAHAEBVItemStack@@@Z:
    mov rax, [rel Container_vtable]
    jmp [rax + 224]
    
global ?setContainerChanged@Container@@UEAAXH@Z
?setContainerChanged@Container@@UEAAXH@Z:
    mov rax, [rel Container_vtable]
    jmp [rax + 248]
    
global ?setContainerMoved@Container@@UEAAXXZ
?setContainerMoved@Container@@UEAAXXZ:
    mov rax, [rel Container_vtable]
    jmp [rax + 256]
    
global ?readAdditionalSaveData@Container@@UEAAXAEBVCompoundTag@@@Z
?readAdditionalSaveData@Container@@UEAAXAEBVCompoundTag@@@Z:
    mov rax, [rel Container_vtable]
    jmp [rax + 280]
    
global ?addAdditionalSaveData@Container@@UEAAXAEAVCompoundTag@@@Z
?addAdditionalSaveData@Container@@UEAAXAEAVCompoundTag@@@Z:
    mov rax, [rel Container_vtable]
    jmp [rax + 288]
    
global ?createTransactionContext@Container@@UEAAXV?$function@$$A6AXAEAVContainer@@HAEBVItemStack@@1@Z@std@@V?$function@$$A6AXXZ@3@@Z
?createTransactionContext@Container@@UEAAXV?$function@$$A6AXAEAVContainer@@HAEBVItemStack@@1@Z@std@@V?$function@$$A6AXXZ@3@@Z:
    mov rax, [rel Container_vtable]
    jmp [rax + 296]
    
global ?isEmpty@Container@@UEBA_NXZ
?isEmpty@Container@@UEBA_NXZ:
    mov rax, [rel Container_vtable]
    jmp [rax + 312]