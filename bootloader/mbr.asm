[bits 16]                   ; Start in 16-bit Real Mode (default CPU state).
[org 0x7c00]                ; Tells the assembler that this code will be loaded at memory address 0x7C00.
                            ; This is the standard boot sector address.

%include "./build/intermediate/kernel_size.inc"
                            ; Includes a file that defines constants related to the kernel,
                            ; specifically 'kernel_sectors' (how much disk space the kernel takes).

kernel_offset equ 0x1000    ; Defines the memory address (1MB or 4KB) where the kernel will be loaded.

mov [boot_drive], dl        ; Save the boot drive number (passed by BIOS in the DL register)
                            ; so it can be used later to read the disk.

mov bp, 0x9000              ; Set the Base Pointer (BP) for the 16-bit stack.
mov sp, bp                  ; Set the Stack Pointer (SP) equal to BP.
                            ; Sets up a temporary stack for the bootloader's operations.

call load_kernel            ; Call the routine (defined below) that reads the kernel from the disk.
call switch_to_32bit        ; Call the routine to transition the CPU from 16-bit to 32-bit Protected Mode.
                            ; This routine is assumed to reside in "./Bootloader/switch_to_32bit_mode.asm".

jmp $                       ; If the previous call fails to transition, loop indefinitely (halt).

%include "./bootloader/disk.asm"
                            ; Includes the assembly routines necessary for disk I/O (e.g., INT 13h calls).
%include "./bootloader/gdt.asm"
                            ; Includes the definition of the Global Descriptor Table (GDT) and its descriptor.
%include "./bootloader/switch_to_32bit_mode.asm"
                            ; Includes the mode switching code (like the previous example).

[bits 16]
load_kernel:
    mov bx, kernel_offset   ; Set the memory address (0x1000) where the disk read operation should place the data.
    mov dh, kernel_sectors  ; Set the number of sectors to read (from the included file).
    mov dl, [boot_drive]    ; Set the boot drive number (from the saved DL register).
    call load_disk          ; Call the disk reading routine (defined in disk.asm).
    ret                     ; Return to the main bootloader code.

[bits 32]                   ; Now in 32-bit mode after 'switch_to_32bit' has executed.
begin_32bit:
    call kernel_offset      ; Jump/call to the memory address where the kernel was loaded (0x1000).
                            ; This begins execution of the kernel's C code entry point.
    jmp $                   ; If the kernel returns (which it shouldn't), halt the system.

boot_drive db 0             ; Storage variable to hold the saved boot drive number.

times 510 - ($-$$) db 0     ; Pad the boot sector with zeros up to byte 510.

dw 0xaa55                   ; The mandatory boot sector signature (511th and 512th bytes).
                            ; This tells the BIOS that the sector is bootable.