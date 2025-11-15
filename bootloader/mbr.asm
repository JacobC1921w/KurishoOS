[bits 16]
[org 0x7c00]

%include "./build/intermediate/kernel_size.inc"

kernel_offset equ 0x1000

mov [boot_drive], dl

mov bp, 0x9000
mov sp, bp

call load_kernel
call switch_to_32bit

jmp $

%include "./bootloader/disk.asm"
%include "./bootloader/gdt.asm"
%include "./bootloader/switch_to_32bit_mode.asm"

[bits 16]
load_kernel:
    mov bx, kernel_offset
    mov dh, kernel_sectors
    mov dl, [boot_drive]
    call load_disk
    ret

[bits 32]
begin_32bit:
    call kernel_offset
    jmp $

boot_drive db 0

times 510 - ($-$$) db 0

dw 0xaa55