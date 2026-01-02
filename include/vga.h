#pragma once
#include "../include/types.h"

void vga_clear(void);
void vga_write(const char* str);
void vga_set_color(u8 color);
void vga_putc(char c);
void vga_scroll(void);