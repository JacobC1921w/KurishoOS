[extern ISRHandler]
[extern IRQHandler]

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
    jmp ISRCommonStub

isr1:
    push byte 0
    push byte 1
    jmp ISRCommonStub

isr2:
    push byte 0
    push byte 2
    jmp ISRCommonStub

isr3:
    push byte 0
    push byte 3
    jmp ISRCommonStub

isr4:
    push byte 0
    push byte 4
    jmp ISRCommonStub

isr5:
    push byte 0
    push byte 5
    jmp ISRCommonStub

isr6:
    push byte 0
    push byte 6
    jmp ISRCommonStub

isr7:
    push byte 0
    push byte 7
    jmp ISRCommonStub

isr8:
    push byte 8
    jmp ISRCommonStub

isr9:
    push byte 0
    push byte 9
    jmp ISRCommonStub

isr10:
    push byte 10
    jmp ISRCommonStub

isr11:
    push byte 11
    jmp ISRCommonStub

isr12:
    push byte 12
    jmp ISRCommonStub

isr13:
    push byte 13
    jmp ISRCommonStub

isr14:
    push byte 14
    jmp ISRCommonStub

isr15:
    push byte 0
    push byte 15
    jmp ISRCommonStub

isr16:
    push byte 0
    push byte 16
    jmp ISRCommonStub

isr17:
    push byte 0
    push byte 17
    jmp ISRCommonStub

isr18:
    push byte 0
    push byte 18
    jmp ISRCommonStub

isr19:
    push byte 0
    push byte 19
    jmp ISRCommonStub

isr20:
    push byte 0
    push byte 20
    jmp ISRCommonStub

isr21:
    push byte 0
    push byte 21
    jmp ISRCommonStub

isr22:
    push byte 0
    push byte 22
    jmp ISRCommonStub

isr23:
    push byte 0
    push byte 23
    jmp ISRCommonStub

isr24:
    push byte 0
    push byte 24
    jmp ISRCommonStub

isr25:
    push byte 0
    push byte 25
    jmp ISRCommonStub

isr26:
    push byte 0
    push byte 26
    jmp ISRCommonStub

isr27:
    push byte 0
    push byte 27
    jmp ISRCommonStub

isr28:
    push byte 0
    push byte 28
    jmp ISRCommonStub

isr29:
    push byte 0
    push byte 29
    jmp ISRCommonStub

isr30:
    push byte 0
    push byte 30
    jmp ISRCommonStub

isr31:
    push byte 0
    push byte 31
    jmp ISRCommonStub

ISRCommonStub:
    pusha

    mov ax, ds
    push eax

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    push esp
    call ISRHandler
    pop eax

    pop eax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    popa

    add esp, 8

    iret

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
    jmp IRQCommonStub

irq1:
    push byte 1
    push byte 33
    jmp IRQCommonStub

irq2:
    push byte 2
    push byte 34
    jmp IRQCommonStub

irq3:
    push byte 3
    push byte 35
    jmp IRQCommonStub

irq4:
    push byte 4
    push byte 36
    jmp IRQCommonStub

irq5:
    push byte 5
    push byte 37
    jmp IRQCommonStub

irq6:
    push byte 6
    push byte 38
    jmp IRQCommonStub

irq7:
    push byte 7
    push byte 39
    jmp IRQCommonStub

irq8:
    push byte 8
    push byte 40
    jmp IRQCommonStub

irq9:
    push byte 9
    push byte 41
    jmp IRQCommonStub

irq10:
    push byte 10
    push byte 42
    jmp IRQCommonStub

irq11:
    push byte 11
    push byte 43
    jmp IRQCommonStub

irq12:
    push byte 12
    push byte 44
    jmp IRQCommonStub

irq13:
    push byte 13
    push byte 45
    jmp IRQCommonStub

irq14:
    push byte 14
    push byte 46
    jmp IRQCommonStub

irq15:
    push byte 15
    push byte 47
    jmp IRQCommonStub

IRQCommonStub:
    pusha

    mov ax, ds
    push eax

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    push esp

    call IRQHandler

    pop ebx

    pop eax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    popa

    add esp, 8

    iret