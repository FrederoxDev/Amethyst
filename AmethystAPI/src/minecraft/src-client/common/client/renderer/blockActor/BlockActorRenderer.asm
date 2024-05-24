section .text

extern BlockActorRenderer_vtable

global ??1BlockActorRenderer@@UEAA@XZ
??1BlockActorRenderer@@UEAA@XZ:
    mov rax, [rel BlockActorRenderer_vtable]
	jmp [rax + 0]

global ?_getOverlayColor@BlockActorRenderer@@UEBA?AVColor@mce@@AEAVActor@@M@Z
?_getOverlayColor@BlockActorRenderer@@UEBA?AVColor@mce@@AEAVActor@@M@Z:
    mov rax, [rel BlockActorRenderer_vtable]
	jmp [rax + 8]

global ?extractText@BlockActorRenderer@@UEAA?AV?$vector@VNameTagRenderObject@@V?$allocator@VNameTagRenderObject@@@std@@@std@@AEAVTessellator@@AEAVBlockActor@@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@3@AEAV?$vector@HV?$allocator@H@std@@@3@VVec3@@_N@Z
?extractText@BlockActorRenderer@@UEAA?AV?$vector@VNameTagRenderObject@@V?$allocator@VNameTagRenderObject@@@std@@@std@@AEAVTessellator@@AEAVBlockActor@@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@3@AEAV?$vector@HV?$allocator@H@std@@@3@VVec3@@_N@Z:
    mov rax, [rel BlockActorRenderer_vtable]
	jmp [rax + 32]