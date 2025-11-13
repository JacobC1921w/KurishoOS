gdt_start:
    dq 0x0                      ; 8-byte quad-word set to zero.

gdt_code:
    dw 0xffff                   ; Limit (low 16 bits): Defines the segment size. 0xFFFF here.
    dw 0x0                      ; Base (low 16 bits): Base address of the segment (0x0).
    db 0x0                      ; Base (middle 8 bits): (0x0).
    db 10011010b                ; Access Byte (Flags): P=1, DPL=0 (Kernel), S=1 (Code/Data), Type=1010b (Code, Read/Execute).
    db 11001111b                ; High Flags/Limit: G=1 (4KB granularity), D/B=1 (32-bit segment), Limit (high 4 bits).
    db 0x0                      ; Base (high 8 bits): (0x0).

gdt_data:
    dw 0xffff                   ; Limit (low 16 bits): 0xFFFF.
    dw 0x0                      ; Base (low 16 bits): 0x0.
    db 0x0                      ; Base (middle 8 bits): 0x0.
    db 10010010b                ; Access Byte (Flags): P=1, DPL=0 (Kernel), S=1 (Code/Data), Type=0010b (Data, Read/Write).
    db 11001111b                ; High Flags/Limit: G=1 (4KB granularity), D/B=1 (32-bit segment), Limit (high 4 bits).
    db 0x0                      ; Base (high 8 bits): 0x0.

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1  ; Limit: The size of the GDT table in bytes (minus 1).
    dd gdt_start                ; Base: The 32-bit memory address where the GDT starts.

code_segment equ gdt_code - gdt_start
dataSeg equ gdt_data - gdt_start