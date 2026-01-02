#include "../../include/regs.h"
#include "../../include/timer.h"
#include "../../include/scheduler.h"

uint32_t irq_handler_c(uint32_t esp) {
    registers_t *regs = (registers_t*)esp;

    // apenas se for PIT
    if (regs->int_no == 32) {
        timer_callback(regs);
    }

    // devolve o novo ESP da próxima task
    return scheduler_tick(esp);
}
