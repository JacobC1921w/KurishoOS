globalDescriptorTableStart:
    dq 0x0

globalDescriptorTableCode:
    dw 0xffff
    dw 0x0
    db 0x0
    db 10011010b
    db 11001111b
    db 0x0

globalDescriptorTableData:
    dw 0xffff
    dw 0x0
    db 0x0
    db 10010010b
    db 11001111b
    db 0x0

globalDescriptorTableEnd:

; GDT descriptor
globalDescriptorTableDescriptor:
    dw globalDescriptorTableEnd - globalDescriptorTableStart - 1
    dd globalDescriptorTableStart

codeSeg equ globalDescriptorTableCode - globalDescriptorTableStart
dataSeg equ globalDescriptorTableData - globalDescriptorTableStart