[bits 16]
[org 0x7c00]

%include "./Build/Intermediate/kernelSize.inc"

kernelOffset equ 0x1000

mov [bootDrive], dl

mov bp, 0x9000
mov sp, bp

call loadKernel
call switchTo32BitMode

jmp $

%include "./Bootloader/disk.asm"
%include "./Bootloader/globalDescriptorTable.asm"
%include "./Bootloader/switchTo32Bit.asm"

[bits 16]
loadKernel:
    mov bx, kernelOffset
    mov dh, kernelSectors
    mov dl, [bootDrive]
    call diskLoad
    ret

[bits 32]
begin32BitMode:
    call kernelOffset
    jmp $

bootDrive db 0

times 510 - ($-$$) db 0

dw 0xaa55