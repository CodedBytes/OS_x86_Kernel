#pragma once
#include <stdint.h>
#include "isr.h"

void pit_init(int hz);
void pit_callback(registers_t *regs);