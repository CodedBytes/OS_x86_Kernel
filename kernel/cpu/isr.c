#include "isr.h"
#include "io.h"

static isr_t interrupt_handlers[256];

void isr_install_handler(uint8_t n, isr_t handler) {
    interrupt_handlers[n] = handler;
}

void irq_install_handler(uint8_t irq, isr_t handler) {
    interrupt_handlers[32 + irq] = handler;
}

void isr_uninstall_handler(uint8_t n) {
    interrupt_handlers[n] = 0;
}

void isr_handler(registers_t *regs) {
    while (1) __asm__ volatile ("hlt");
}

void irq_handler(registers_t *regs) {
    if (interrupt_handlers[regs->int_no]) {
        interrupt_handlers[regs->int_no](regs);
    }

    if (regs->int_no >= 40)
        outb(0xA0, 0x20);

    outb(0x20, 0x20);
}
