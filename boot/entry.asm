global _start
extern kernel_main

section .text
bits 32

_start:
    cli
    mov esp, stack_top       ; stack simples

    mov eax, ebx             ; ponteiro multiboot_info
    push eax
    call kernel_main
    add esp, 4

.hang:
    hlt
    jmp .hang

section .bss
align 16
stack_bottom:
    resb 16384
stack_top:
