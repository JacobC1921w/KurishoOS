diskLoad:
    pusha
    push dx

    mov ah, 0x02
    mov al, dh
    mov cl, 0x02
                 
    mov ch, 0x00
    mov dh, 0x00

    int 0x13
    jc diskError

    pop dx
    cmp al, dh
               
    jne sectorError
    popa
    ret

diskError:
    jmp diskLoop

sectorError:
    jmp diskLoop

diskLoop:
    jmp $