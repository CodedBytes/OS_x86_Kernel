#include "../include/scheduler.h"
#include "../include/log.h"
#include "../include/task.h"

static task_t tasks[MAX_TASKS];
static int task_count = 0;
static int current_task = -1;

extern void context_switch(uint32_t *old_esp, uint32_t new_esp);

void scheduler_init(void) {
    log_info("Scheduler init");
}

void scheduler_add(void (*entry)(void)) {
    task_t *t = &tasks[task_count];
    uint32_t *stack = (uint32_t *)&t->stack[STACK_SIZE];

    // Frame de interrupção (IRET)
    *(--stack) = 0x202; // EFLAGS
    *(--stack) = 0x08;  // CS
    *(--stack) = (uint32_t)entry; // EIP

    // Erro de código e número da interrupção (add esp, 8 no stub)
    *(--stack) = 0; 
    *(--stack) = 32;

    // Pusha (8 registradores)
    for(int i=0; i<8; i++) *(--stack) = 0;

    // Segmentos (DS, ES, FS, GS)
    *(--stack) = 0x10;
    *(--stack) = 0x10;
    *(--stack) = 0x10;
    *(--stack) = 0x10;

    t->esp = (uint32_t)stack;
    task_count++;
}

uint32_t scheduler_tick(uint32_t current_esp) {
    if (task_count < 2) return current_esp;

    // Salva o ESP da task que estava rodando
    tasks[current_task].esp = current_esp;

    // Alterna
    current_task = (current_task + 1) % task_count;

    return tasks[current_task].esp;
}