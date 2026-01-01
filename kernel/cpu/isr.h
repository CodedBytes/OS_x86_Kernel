#pragma once
#include <stdint.h>

/* Estrutura dos registradores empilhados pelo stub ASM */
typedef struct registers {
    uint32_t gs, fs, es, ds;          // pushed manually
    uint32_t edi, esi, ebp, esp;
    uint32_t ebx, edx, ecx, eax;      // pusha
    uint32_t int_no, err_code;        // pushed before stub
    uint32_t eip, cs, eflags, useresp, ss;
} registers_t;

/* Handler C genérico */
typedef void (*isr_t)(registers_t *);

/* Funções públicas */
void isr_install(void);
void irq_install(void);

void isr_handler(registers_t *regs);
void irq_handler(registers_t *regs);

/* Registro dinâmico de handlers */
void isr_install_handler(uint8_t n, isr_t handler);
void irq_install_handler(uint8_t irq, isr_t handler);
void isr_uninstall_handler(uint8_t n);
