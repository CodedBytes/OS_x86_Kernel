[bits 32]

extern isr_handler
global isr0

isr0:
    cli
    push dword 0
    push dword 0
    jmp isr_common_stub

isr_common_stub:
    pusha
    push ds
    push es
    push fs
    push gs

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    push esp
    call isr_handler
    add esp, 4

    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8
    sti
    iretd
