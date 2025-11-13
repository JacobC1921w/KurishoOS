[bits 32]               ; Ensures the assembler generates 32-bit instructions.

[extern main]           ; Declares that the symbol 'main' is defined externally (usually in a C file).
                        ; This is a linker directive, not an executable instruction.

call main               ; The core function: Transfers execution control to the high-level C function named 'main'.
                        ; This is the official entry point of the C-based kernel.

jmp $                   ; Loop indefinitely (infinite loop). If the 'main' function ever returns,
                        ; the CPU will halt execution at this address, preventing uncontrolled behavior.