load_disk:
    pusha                   ; Save all general-purpose registers (standard procedure before a function call).
    push dx                 ; Save DX register (contains the boot drive number in DL and sectors to read in DH),
                            ; as we'll modify it and need the original sectors-to-read value later.

    ; --- CONFIGURE BIOS INT 13H PARAMETERS ---
    mov ah, 0x02            ; AH = 02h: BIOS function to READ sectors from drive.
    mov al, dh              ; AL = Number of sectors to read. (Moves value from DH, which was set in C code).
    mov cl, 0x02            ; CL = Sector number. Starts reading at Sector 2 (Sector 1 is the bootloader itself).
                            ; Bits 7-6: Cylinder high bits (00). Bits 5-0: Sector number (02h).

    ; Configure Cylinder and Head for starting read position (0, 0, 2).
    mov ch, 0x00            ; CH = Cylinder number (low 8 bits). Set to 0 (first cylinder).
    mov dh, 0x00            ; DH = Head number. Set to 0 (first head/side).
                            ; DL (Drive number) is already set from the caller function.
    ; ES:BX (Data buffer address) is assumed to be set by the caller (likely set to 0x0000:0x1000).

    ; --- EXECUTE I/O AND ERROR CHECK ---
    int 0x13                ; Call BIOS Disk Services (Interrupt 13h) to perform the read operation.
    jc disk_error           ; JUMP if CARRY flag is set (C=1). BIOS sets the CARRY flag on failure.

    ; --- SUCCESS CHECK (DID WE READ ENOUGH?) ---
    pop dx                  ; Restore original DX (DH now contains the number of sectors we INTENDED to read).
    cmp al, dh              ; Compare AL (Sectors ACTUALLY read, returned by BIOS) with DH (Sectors REQUESTED).

    jne sector_error        ; JUMP if not equal. If actual sectors read != requested sectors, it's an error.
    popa                    ; Restore all general-purpose registers (from step 1).
    ret                     ; Return successfully to the calling code.

; --- ERROR HANDLERS ---
disk_error:
    jmp disk_loop           ; Jump to infinite loop on critical BIOS error.

sector_error:
    jmp disk_loop           ; Jump to infinite loop on reading the wrong number of sectors.

disk_loop:
    jmp $                   ; Infinite loop (Halt/Hang) - The typical response for an unrecoverable boot error.