BITS 32

extern irq_handler_c

global irq0_handler

irq0_handler:
    pusha
    call irq_handler_c
    popa
    mov al, 0x20
    out 0x20, al
    iret
