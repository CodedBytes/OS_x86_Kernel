#pragma once
#include "../include/types.h"
#include "../include/regs.h"

void pit_init(uint32_t freq);
void timer_callback(registers_t *regs);