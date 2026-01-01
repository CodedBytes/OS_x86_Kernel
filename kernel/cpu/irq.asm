[bits 32]

extern irq_handler
global irq0
global irq1

irq0:               ; PIT
    cli
    push dword 0
    push dword 32
    jmp irq_common_stub

irq1:               ; KEYBOARD
    cli
    push dword 0
    push dword 33
    jmp irq_common_stub

irq_common_stub:
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
    call irq_handler
    add esp, 4

    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8
    sti
    iretd
