#include <stdint.h>
#include "../include/kernel.h"
#include "../include/vga.h"
#include "../include/arch.h"
#include "../include/gdt.h"
#include "../include/idt.h"
#include "../include/pic.h"
#include "../include/timer.h"

void kernel_main(void) {
    vga_clear();

    log_info("Kernel iniciado");
    log_info("Infraestrutura basica OK");
    log_warn("Teste de aviso");
    log_error("Teste de erro");

    //log_info("CPU abstraida");
    //cpu_cli();
    //log_info("CLI OK");
    //cpu_sti();
    //log_info("STI OK");
    // EStas nao podem ser chamdas agora pois vai dar triple fault

    log_info("GDT");
    gdt_load();

    log_info("IDT");
    idt_init();

    log_info("Remap PIC");
    pic_remap(32, 40);

    log_info("Init PIT");
    pit_init(100);

    log_info("Enable IRQ");
    cpu_sti();

    while (1) {
        cpu_halt();
    }
}