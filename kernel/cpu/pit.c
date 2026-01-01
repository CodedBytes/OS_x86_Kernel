#include "pit.h"
#include "isr.h"
#include "io.h"


static uint32_t tick = 0;

void pit_callback(registers_t *regs) {
    (void)regs;
    tick++;
    schedule();
    task_yield(); 
}

void pit_init(int hz) {
    // O divisor de PIT é calculado em relação à frequência do sistema.
    uint32_t divisor = 1193180 / hz;

    // Envia o comando para o PIT (porta 0x43) para definir a frequência.
    outb(0x36, 0x43);

    // Envia o divisor para os registros de dados (porta 0x40).
    outb((uint8_t)(divisor & 0xFF), 0x40); // LSB
    outb((uint8_t)((divisor >> 8) & 0xFF), 0x40); // MSB

    irq_install_handler(0, pit_callback);
}
