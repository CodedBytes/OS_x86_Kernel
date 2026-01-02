#pragma once
#include <stdint.h>

#define MAX_TASKS 4
#define STACK_SIZE 8192

typedef struct task {
    uint32_t *esp;            // topo da stack
    uint32_t stack[STACK_SIZE];
    uint8_t active;
    uint8_t id;
} task_t;

// funções do scheduler
void scheduler_init(void);
void scheduler_add(void (*entry)(void));
uint32_t scheduler_tick(uint32_t current_esp);
