#include <stdint.h>
#include "../include/vga.h"

static uint16_t* vga_buffer = (uint16_t*)0xB8000;
static uint8_t cursor_x = 0;
static uint8_t cursor_y = 0;
static uint8_t current_color = 0x07;

static uint16_t vga_entry(char c, uint8_t color) {
    return (uint16_t)c | ((uint16_t)color << 8);
}

void vga_scroll(void) {
    if (cursor_y < 25) return;

    for (int y = 1; y < 25; y++) {
        for (int x = 0; x < 80; x++) {
            vga_buffer[(y - 1) * 80 + x] = vga_buffer[y * 80 + x];
        }
    }

    for (int x = 0; x < 80; x++) {
        vga_buffer[(24) * 80 + x] = 0x0720;
    }

    cursor_y = 24;
}

void safe_vga_putc(char c) {
    cpu_cli(); // Desabilita interrupções
    vga_putc(c);
    cpu_sti(); // Habilita de volta
}

void vga_putc(char c) {
    if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
    } else {
        vga_buffer[cursor_y * 80 + cursor_x] = (0x07 << 8) | c;
        cursor_x++;
    }

    if (cursor_x >= 80) {
        cursor_x = 0;
        cursor_y++;
    }

    vga_scroll();
}

void vga_set_color(u8 color) {
    current_color = color;
}

void vga_clear(void) {
    for (int i = 0; i < 80 * 25; i++) {
        vga_buffer[i] = vga_entry(' ', current_color);
    }
    cursor_x = cursor_y = 0;
}

void vga_write(const char* str) {
    while (*str) {
        if (*str == '\n') {
            cursor_x = 0;
            cursor_y++;
        } else {
            vga_buffer[cursor_y * 80 + cursor_x] =
                vga_entry(*str, current_color);
            cursor_x++;
        }
        str++;
    }
}
