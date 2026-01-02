#include <stdint.h>
#include "../include/kernel.h"
#include "../include/vga.h"
#include "../include/arch.h"
#include "../include/gdt.h"
#include "../include/idt.h"
#include "../include/pic.h"
#include "../include/timer.h"
#include "../include/scheduler.h"

void task_lock(void) {
    uint32_t local = 0;
    while (1) {
        local++;
        if ((local % 100000) == 0) {
            safe_vga_putc('S');
        }
    }
}
void task_tick(void) {
    while (1) {
        safe_vga_putc('O');
        for (volatile int i = 0; i < 500000; i++);
    }
}


void kernel_main(void) {
    vga_clear();

    safe_vga_putc("Kernel iniciado");
    safe_vga_putc("Infraestrutura basica OK");
    log_warn("Teste de aviso");
    log_error("Teste de erro");

    //safe_vga_putc("CPU abstraida");
    cpu_cli();
    safe_vga_putc("CLI OK");
    // EStas nao podem ser chamdas agora pois vai dar triple fault

    safe_vga_putc("GDT");
    gdt_load();

    safe_vga_putc("IDT");
    idt_init();

    safe_vga_putc("Remap PIC");
    pic_remap(32, 40);

    safe_vga_putc("Init PIT");
    pit_init(100);

    scheduler_init();
    scheduler_add(task_lock);
    scheduler_add(task_tick);

    cpu_sti();
    safe_vga_putc("STI OK");

    while (1) {
        cpu_halt();
    }
}