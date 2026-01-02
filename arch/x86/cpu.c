#include "../../include/arch.h"

void cpu_cli(void) {
    __asm__ volatile ("cli");
}

void cpu_sti(void) {
    __asm__ volatile ("sti");
}

void cpu_halt(void) {
    __asm__ volatile ("hlt");
}