BITS 32

extern irq_handler_c

global irq0_stub

irq0_stub:
    push dword 0        ; err_code (fake)
    push dword 32       ; IRQ0 = int 32
    jmp irq_common_stub

irq_common_stub:
    pusha
    push ds
    push es
    push fs
    push gs

    push esp                ; Passa o ESP atual (com todo o contexto salvo)
    call irq_handler_c      ; No seu C, chame scheduler_tick e retorne o novo ESP
    mov esp, eax            ; A MÁGICA: O retorno do C (EAX) vira o novo ESP

    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8
    
    mov al, 0x20            ; EOI
    out 0x20, al
    iret