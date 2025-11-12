[bits 16]
switchTo32BitMode:
    cli
    lgdt [globalDescriptorTableDescriptor]
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax
    jmp codeSeg:initialize32BitMode

[bits 32]
initialize32BitMode:
    mov ax, dataSeg
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000
    mov esp, ebp

    call begin32BitMode