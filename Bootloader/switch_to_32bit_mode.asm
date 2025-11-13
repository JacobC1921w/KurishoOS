[bits 16]                   ; Tells the assembler to generate 16-bit instructions.

switch_to_32bit:
    cli                     ; Clear Interrupts. Disable hardware interrupts to prevent
                            ; interference during the critical mode switch.

    lgdt [gdt_descriptor]   ; Load Global Descriptor Table (GDT). Loads the address and size
                            ; of the GDT into the CPU's GDTR register. The GDT defines the
                            ; memory segments for Protected Mode.

    mov eax, cr0            ; Move the contents of Control Register 0 (CR0) into EAX.
    or eax, 0x1             ; Set the Protection Enable (PE) bit (bit 0) in CR0.
                            ; Setting this bit enables Protected Mode.
    mov cr0, eax            ; Write the modified value back to CR0, activating Protected Mode.

    ; Far Jump to flush the instruction prefetch queue and load the new CS (Code Segment)
    ; register with a 32-bit descriptor from the GDT. Execution continues at initialize_32bit.
    jmp code_segment:initialize_32bit

[bits 32]                   ; Tells the assembler that all subsequent instructions are 32-bit.

initialize_32bit:
    ; --- 1. Initialize Segment Registers ---
    ; Set up the segment registers to use the new 32-bit data segment defined in the GDT.
    ; This establishes a 'flat' memory model where DS=SS=ES=FS=GS.
    mov ax, dataSeg         ; Load the GDT selector for the data segment.
    mov ds, ax              ; Set Data Segment (DS)
    mov ss, ax              ; Set Stack Segment (SS)
    mov es, ax              ; Set Extra Segment (ES)
    mov fs, ax              ; Set FS segment
    mov gs, ax              ; Set GS segment

    ; --- 2. Set Up Stack ---
    ; Establish the stack pointer for 32-bit operations.
    mov ebp, 0x90000        ; Set the Base Pointer (EBP) to a high memory address.
    mov esp, ebp            ; Set the Stack Pointer (ESP) equal to EBP.
                            ; The stack now grows downwards from 0x90000.

    ; --- 3. Start C Code ---
    call begin_32bit        ; Call the entry point function written in C (or higher-level assembly),
                            ; transferring control to the 32-bit operating system kernel.