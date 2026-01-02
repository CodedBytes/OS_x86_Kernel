; arch/x86/boot.asm
BITS 32

SECTION .multiboot
align 4
dd 0x1BADB002
dd 0x00000000
dd -(0x1BADB002)

SECTION .text
global _start
extern kernel_main

_start:
    cli

    mov esp, stack_top
    mov ebp, esp

    call kernel_main

.hang:
    hlt
    jmp .hang

SECTION .bss
align 16
stack_bottom:
    resb 16384
stack_top:
