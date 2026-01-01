#pragma once
#include <stdint.h>

void pic_remap(void);
void pic_send_eoi(int irq);
void pic_clear_mask(uint8_t irq);
