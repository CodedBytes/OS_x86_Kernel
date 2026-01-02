#include "../include/vga.h"

void kernel_panic(const char* msg) {
    vga_set_color(0x0C); // vermelho

    vga_write("!!! KERNEL PANIC !!!\n\n");
    vga_write(msg);

    __asm__ volatile ("cli");
    for (;;) {
        __asm__ volatile ("hlt");
    }
}
