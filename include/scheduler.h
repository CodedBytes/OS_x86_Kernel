#pragma once
#include <stdint.h>
#include "../include/regs.h"
#include <stddef.h>


#define MAX_TASKS 8

typedef void (*task_func_t)(void);

void scheduler_init(void);
void scheduler_add(void (*entry)(void));
uint32_t scheduler_tick(uint32_t current_esp) ;