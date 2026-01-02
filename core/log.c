#include "../include/vga.h"

#define COLOR_INFO  0x0A  // verde
#define COLOR_WARN  0x0E  // amarelo
#define COLOR_ERR   0x0C  // vermelho
#define COLOR_RESET 0x07  // cinza

static void log_prefix(const char* pfx, u8 color) {
    vga_set_color(color);
    vga_write("[");
    vga_write(pfx);
    vga_write("]");
    vga_set_color(COLOR_RESET);
    vga_write(" ");
}

void log_info(const char* msg) {
    log_prefix("INFO", COLOR_INFO);
    vga_write(msg);
    vga_write("\n");
}

void log_warn(const char* msg) {
    log_prefix("WARN", COLOR_WARN);
    vga_write(msg);
    vga_write("\n");
}

void log_error(const char* msg) {
    log_prefix("ERR", COLOR_ERR);
    vga_write(msg);
    vga_write("\n");
}