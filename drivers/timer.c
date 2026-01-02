#include "../include/vga.h"
#include "../include/io.h"
#include "../include/timer.h"
#include "../include/scheduler.h"

#define PIT_CHANNEL0 0x40
#define PIT_COMMAND  0x43
#define PIT_FREQ     1193182

static u32 ticks = 0;

void pit_init(u32 freq) {
    u32 divisor = PIT_FREQ / freq;

    outb(PIT_COMMAND, 0x36);
    outb(PIT_CHANNEL0, divisor & 0xFF);
    outb(PIT_CHANNEL0, (divisor >> 8) & 0xFF);
}

void timer_callback(registers_t *regs) {
    (void)regs;

    ticks++;
    if (ticks % 100 == 0) {
        vga_write(".");
    }
}
