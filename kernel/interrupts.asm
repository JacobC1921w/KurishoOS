[extern isr_handler]
[extern irq_handler]

global isr0
global isr1
global isr2
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr9
global isr10
global isr11
global isr12
global isr13
global isr14
global isr15
global isr16
global isr17
global isr18
global isr19
global isr20
global isr21
global isr22
global isr23
global isr24
global isr25
global isr26
global isr27
global isr28
global isr29
global isr30
global isr31

isr0:
    push byte 0
    push byte 0
    jmp isr_common_stub

isr1:
    push byte 0
    push byte 1
    jmp isr_common_stub

isr2:
    push byte 0
    push byte 2
    jmp isr_common_stub

isr3:
    push byte 0
    push byte 3
    jmp isr_common_stub

isr4:
    push byte 0
    push byte 4
    jmp isr_common_stub

isr5:
    push byte 0
    push byte 5
    jmp isr_common_stub

isr6:
    push byte 0
    push byte 6
    jmp isr_common_stub

isr7:
    push byte 0
    push byte 7
    jmp isr_common_stub

isr8:
    push byte 8
    jmp isr_common_stub

isr9:
    push byte 0
    push byte 9
    jmp isr_common_stub

isr10:
    push byte 10
    jmp isr_common_stub

isr11:
    push byte 11
    jmp isr_common_stub

isr12:
    push byte 12
    jmp isr_common_stub

isr13:
    push byte 13
    jmp isr_common_stub

isr14:
    push byte 14
    jmp isr_common_stub

isr15:
    push byte 0
    push byte 15
    jmp isr_common_stub

isr16:
    push byte 0
    push byte 16
    jmp isr_common_stub

isr17:
    push byte 0
    push byte 17
    jmp isr_common_stub

isr18:
    push byte 0
    push byte 18
    jmp isr_common_stub

isr19:
    push byte 0
    push byte 19
    jmp isr_common_stub

isr20:
    push byte 0
    push byte 20
    jmp isr_common_stub

isr21:
    push byte 0
    push byte 21
    jmp isr_common_stub

isr22:
    push byte 0
    push byte 22
    jmp isr_common_stub

isr23:
    push byte 0
    push byte 23
    jmp isr_common_stub

isr24:
    push byte 0
    push byte 24
    jmp isr_common_stub

isr25:
    push byte 0
    push byte 25
    jmp isr_common_stub

isr26:
    push byte 0
    push byte 26
    jmp isr_common_stub

isr27:
    push byte 0
    push byte 27
    jmp isr_common_stub

isr28:
    push byte 0
    push byte 28
    jmp isr_common_stub

isr29:
    push byte 0
    push byte 29
    jmp isr_common_stub

isr30:
    push byte 0
    push byte 30
    jmp isr_common_stub

isr31:
    push byte 0
    push byte 31
    jmp isr_common_stub

isr_common_stub:
    ; --- 1. SAVE CONTEXT (PUSH REGISTERS) ---
    pusha                   ; Pushes all general-purpose registers (EAX, ECX, EDX, EBX, ESP, EBP, ESI, EDI).

    ; Save the current Data Segment (DS) register value.
    ; DS is 16-bit, but we need to save it as 32-bit (EAX) on the stack.
    mov ax, ds
    push eax

    ; --- 2. SET UP KERNEL SEGMENTS ---
    ; Set up flat memory model for the C handler.
    ; 0x10 is the kernel data segment selector.
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ; --- 3. CALL C HANDLER ---
    ; Push the stack pointer (ESP) before calling the C handler.
    ; This passes a pointer to the saved registers (the 'registers *reg' argument)
    ; as the C function argument (C calling convention).
    push esp
    call isr_handler        ; Call the C-level exception handler.
    pop eax                 ; Clean up the pushed ESP argument from the stack.

    ; --- 4. RESTORE SEGMENTS ---
    ; Restore the original Data Segment value (EAX was used to save it).
    pop eax                 ; Restore the original DS value into EAX.
    mov ds, ax              ; Restore the original DS register.
    mov es, ax              ; Restore other segment registers (ES, FS, GS) as well.
    mov fs, ax
    mov gs, ax

    ; --- 5. RESTORE CONTEXT AND RETURN ---
    popa                    ; Restores all general-purpose registers (from step 1).

    ; The interrupt vector number and an optional error code were pushed
    ; onto the stack by the CPU or a preceding assembly stub.
    ; We skip them here to balance the stack for the IRET instruction.
    ; The number of bytes to pop (8) is calculated based on the size of
    ; the pushed vector number (4 bytes) and the error code (4 bytes).
    add esp, 8

    iret                    ; Return from interrupt. Restores EIP, CS, EFLAGS from stack.

global irq0
global irq1
global irq2
global irq3
global irq4
global irq5
global irq6
global irq7
global irq8
global irq9
global irq10
global irq11
global irq12
global irq13
global irq14
global irq15

irq0:
    push byte 0
    push byte 32
    jmp irq_common_stub

irq1:
    push byte 1
    push byte 33
    jmp irq_common_stub

irq2:
    push byte 2
    push byte 34
    jmp irq_common_stub

irq3:
    push byte 3
    push byte 35
    jmp irq_common_stub

irq4:
    push byte 4
    push byte 36
    jmp irq_common_stub

irq5:
    push byte 5
    push byte 37
    jmp irq_common_stub

irq6:
    push byte 6
    push byte 38
    jmp irq_common_stub

irq7:
    push byte 7
    push byte 39
    jmp irq_common_stub

irq8:
    push byte 8
    push byte 40
    jmp irq_common_stub

irq9:
    push byte 9
    push byte 41
    jmp irq_common_stub

irq10:
    push byte 10
    push byte 42
    jmp irq_common_stub

irq11:
    push byte 11
    push byte 43
    jmp irq_common_stub

irq12:
    push byte 12
    push byte 44
    jmp irq_common_stub

irq13:
    push byte 13
    push byte 45
    jmp irq_common_stub

irq14:
    push byte 14
    push byte 46
    jmp irq_common_stub

irq15:
    push byte 15
    push byte 47
    jmp irq_common_stub

irq_common_stub:
    ; --- 1. SAVE CONTEXT (PUSH REGISTERS) ---
    pusha                   ; Save all general-purpose registers (EAX, ECX, etc.).

    ; Save the current Data Segment (DS) register value.
    ; DS is 16-bit, pushed as a 32-bit value (EAX) onto the stack.
    mov ax, ds
    push eax

    ; --- 2. SET UP KERNEL SEGMENTS ---
    ; Set up the kernel data segment (0x10) for the C handler's execution.
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ; --- 3. CALL C HANDLER ---
    ; Push the stack pointer (ESP). This passes a pointer to the saved
    ; registers (the 'registers *reg' argument) to the C handler.
    push esp
    call irq_handler        ; Call the C-level Hardware Interrupt Request handler.
    pop ebx                 ; Clean up the pushed ESP argument from the stack.
                            ; (Uses EBX instead of EAX, but the effect is the same: stack cleanup).

    ; --- 4. RESTORE SEGMENTS ---
    ; Restore the original Data Segment value.
    pop eax                 ; Restore original DS value from stack into EAX.
    mov ds, ax              ; Restore the original DS register.
    mov es, ax              ; Restore other segment registers (ES, FS, GS) as well.
    mov fs, ax
    mov gs, ax

    ; --- 5. RESTORE CONTEXT AND RETURN ---
    popa                    ; Restore all general-purpose registers (from step 1).

    ; The interrupt vector number and an optional error code were pushed
    ; onto the stack by the CPU or a preceding assembly stub.
    ; We skip them here. IRQs do not push an error code, so only the 4-byte
    ; interrupt vector number needs to be skipped.
    ; NOTE: The value '8' is used here, implying the preceding code either
    ; unconditionally pushes a dummy error code or the stub is shared with
    ; ISRs that do push error codes. If only the vector number (4 bytes) was pushed,
    ; this should ideally be 'add esp, 4'. Assuming '8' is correct for this setup.
    add esp, 8

    iret                    ; Return from interrupt. Restores EIP, CS, EFLAGS from stack.